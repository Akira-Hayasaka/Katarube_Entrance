// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2004.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include <assert.h>
#include <string.h>
#include "WmlBandedMatrix.h"
using namespace Wml;

//----------------------------------------------------------------------------
template <class Real>
BandedMatrix<Real>::BandedMatrix (int iSize, int iLBands, int iUBands)
{
    assert( iSize > 0 && iLBands >= 0 && iUBands >= 0 );
    assert( iLBands < iSize && iUBands < iSize );

    m_iSize = iSize;
    m_iLBands = iLBands;
    m_iUBands = iUBands;
    Allocate();
}
//----------------------------------------------------------------------------
template <class Real>
BandedMatrix<Real>::BandedMatrix (const BandedMatrix& rkM)
{
    m_afDBand = 0;
    m_aafLBand = 0;
    m_aafUBand = 0;
    *this = rkM;
}
//----------------------------------------------------------------------------
template <class Real>
BandedMatrix<Real>::~BandedMatrix ()
{
    Deallocate();
}
//----------------------------------------------------------------------------
template <class Real>
BandedMatrix<Real>& BandedMatrix<Real>::operator= (const BandedMatrix& rkM)
{
    Deallocate();
    m_iSize = rkM.m_iSize;
    m_iLBands = rkM.m_iLBands;
    m_iUBands = rkM.m_iUBands;
    Allocate();

    memcpy(m_afDBand,rkM.m_afDBand,m_iSize*sizeof(Real));

    int i;
    for (i = 0; i < m_iLBands; i++)
        memcpy(m_aafLBand[i],rkM.m_aafLBand[i],(m_iSize-1-i)*sizeof(Real));

    for (i = 0; i < m_iUBands; i++)
        memcpy(m_aafUBand[i],rkM.m_aafUBand[i],(m_iSize-1-i)*sizeof(Real));

    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
int BandedMatrix<Real>::GetSize () const
{
    return m_iSize;
}
//----------------------------------------------------------------------------
template <class Real>
int BandedMatrix<Real>::GetLBands () const
{
    return m_iLBands;
}
//----------------------------------------------------------------------------
template <class Real>
int BandedMatrix<Real>::GetUBands () const
{
    return m_iUBands;
}
//----------------------------------------------------------------------------
template <class Real>
Real* BandedMatrix<Real>::GetDBand ()
{
    return m_afDBand;
}
//----------------------------------------------------------------------------
template <class Real>
const Real* BandedMatrix<Real>::GetDBand () const
{
    return m_afDBand;
}
//----------------------------------------------------------------------------
template <class Real>
int BandedMatrix<Real>::GetLBandMax (int i) const
{
    assert( 0 <= i && i < m_iLBands );
    return m_iSize-1-i;
}
//----------------------------------------------------------------------------
template <class Real>
Real* BandedMatrix<Real>::GetLBand (int i)
{
    if ( m_aafLBand )
    {
        assert( 0 <= i && i < m_iLBands );
        return m_aafLBand[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
template <class Real>
const Real* BandedMatrix<Real>::GetLBand (int i) const
{
    if ( m_aafLBand )
    {
        assert( 0 <= i && i < m_iLBands );
        return m_aafLBand[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
template <class Real>
int BandedMatrix<Real>::GetUBandMax (int i) const
{
    assert( 0 <= i && i < m_iUBands );
    return m_iSize-1-i;
}
//----------------------------------------------------------------------------
template <class Real>
Real* BandedMatrix<Real>::GetUBand (int i)
{
    if ( m_aafUBand )
    {
        assert( 0 <= i && i < m_iUBands );
        return m_aafUBand[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
template <class Real>
const Real* BandedMatrix<Real>::GetUBand (int i) const
{
    if ( m_aafUBand )
    {
        assert( 0 <= i && i < m_iUBands );
        return m_aafUBand[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
template <class Real>
Real& BandedMatrix<Real>::operator() (int iRow, int iCol)
{
    assert( 0 <= iRow && iRow < m_iSize && 0 <= iCol && iCol < m_iSize );

    int iBand = iCol - iRow;
    if ( iBand > 0 )
    {
        if ( --iBand < m_iUBands && iRow < m_iSize-1-iBand )
            return m_aafUBand[iBand][iRow];
    }
    else if ( iBand < 0 )
    {
        iBand = -iBand;
        if ( --iBand < m_iLBands && iCol < m_iSize-1-iBand )
            return m_aafLBand[iBand][iCol];
    }
    else
    {
        return m_afDBand[iRow];
    }

    static Real s_fDummy = (Real)0.0;
    return s_fDummy;
}
//----------------------------------------------------------------------------
template <class Real>
Real BandedMatrix<Real>::operator() (int iRow, int iCol) const
{
    assert( 0 <= iRow && iRow < m_iSize && 0 <= iCol && iCol < m_iSize );

    int iBand = iCol - iRow;
    if ( iBand > 0 )
    {
        if ( --iBand < m_iUBands && iRow < m_iSize-1-iBand )
            return m_aafUBand[iBand][iRow];
    }
    else if ( iBand < 0 )
    {
        iBand = -iBand;
        if ( --iBand < m_iLBands && iCol < m_iSize-1-iBand )
            return m_aafLBand[iBand][iCol];
    }
    else
    {
        return m_afDBand[iRow];
    }

    return 0.0;
}
//----------------------------------------------------------------------------
template <class Real>
void BandedMatrix<Real>::SetZero ()
{
    assert( m_iSize > 0 );

    memset(m_afDBand,0,m_iSize*sizeof(Real));

    int i;
    for (i = 0; i < m_iLBands; i++)
        memset(m_aafLBand[i],0,(m_iSize-1-i)*sizeof(Real));

    for (i = 0; i < m_iUBands; i++)
        memset(m_aafUBand[i],0,(m_iSize-1-i)*sizeof(Real));
}
//----------------------------------------------------------------------------
template <class Real>
void BandedMatrix<Real>::SetIdentity ()
{
    assert( m_iSize > 0 );

    int i;
    for (i = 0; i < m_iSize; i++)
        m_afDBand[i] = (Real)1.0;

    for (i = 0; i < m_iLBands; i++)
        memset(m_aafLBand[i],0,(m_iSize-1-i)*sizeof(Real));

    for (i = 0; i < m_iUBands; i++)
        memset(m_aafUBand[i],0,(m_iSize-1-i)*sizeof(Real));
}
//----------------------------------------------------------------------------
template <class Real>
void BandedMatrix<Real>::Allocate ()
{
    // assert:  m_iSize, m_iLBands, m_iRBandQuantity already set
    // assert:  m_afDBand, m_aafLBand, m_aafUBand all null

    m_afDBand = new Real[m_iSize];
    memset(m_afDBand,0,m_iSize*sizeof(Real));

    if ( m_iLBands > 0 )
        m_aafLBand = new Real*[m_iLBands];
    else
        m_aafLBand = 0;

    if ( m_iUBands > 0 )
        m_aafUBand = new Real*[m_iUBands];
    else
        m_aafUBand = 0;

    int i;
    for (i = 0; i < m_iLBands; i++)
    {
        m_aafLBand[i] = new Real[m_iSize-1-i];
        memset(m_aafLBand[i],0,(m_iSize-1-i)*sizeof(Real));
    }

    for (i = 0; i < m_iUBands; i++)
    {
        m_aafUBand[i] = new Real[m_iSize-1-i];
        memset(m_aafUBand[i],0,(m_iSize-1-i)*sizeof(Real));
    }
}
//----------------------------------------------------------------------------
template <class Real>
void BandedMatrix<Real>::Deallocate ()
{
    delete[] m_afDBand;

    int i;

    if ( m_aafLBand )
    {
        for (i = 0; i < m_iLBands; i++)
            delete[] m_aafLBand[i];
        delete[] m_aafLBand;
        m_aafLBand = 0;
    }

    if ( m_aafUBand )
    {
        for (i = 0; i < m_iUBands; i++)
            delete[] m_aafUBand[i];
        delete[] m_aafUBand;
        m_aafUBand = 0;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
namespace Wml
{
template class WML_ITEM BandedMatrix<float>;
template class WML_ITEM BandedMatrix<double>;
}
//----------------------------------------------------------------------------
