/*
 * stuart_landau.cpp
 *
 * This example demonstrates how one can use odeint can be used with state types consisting of complex variables.
 *
 * Copyright 2011-2012 Karsten Ahnert
 * Copyright 2011-2013 Mario Mulansky
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>
#include <complex>
#include <array>

#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

//[ stuart_landau_system_function
typedef complex< double > state_type;

struct stuart_landau
{
    double m_eta;
    double m_alpha;

    stuart_landau( double eta = 1.0 , double alpha = 1.0 )
    : m_eta( eta ) , m_alpha( alpha ) { }

    void operator()( const state_type &x , state_type &dxdt , double ) const
    {
        const complex< double > I( 0.0 , 1.0 );
        dxdt = ( 1.0 + m_eta * I ) * x - ( 1.0 + m_alpha * I ) * norm( x ) * x;
    }
};
//]


/*
//[ stuart_landau_system_function_alternative
double eta = 1.0;
double alpha = 1.0;

void stuart_landau( const state_type &x , state_type &dxdt , double t )
{
    const complex< double > I( 0.0 , 1.0 );
    dxdt = ( 1.0 + m_eta * I ) * x - ( 1.0 + m_alpha * I ) * norm( x ) * x;
}
//]
*/


struct streaming_observer
{
    std::ostream& m_out;

    streaming_observer( std::ostream &out ) : m_out( out ) { }

    template< class State >
    void operator()( const State &x , double t ) const
    {
        m_out << t;
        m_out << "\t" << x.real() << "\t" << x.imag() ;
        m_out << "\n";
    }
};




int main()
{
    //[ stuart_landau_integration
    state_type x = complex< double >( 1.0 , 0.0 );

    const double dt = 0.1;

    typedef runge_kutta4< state_type > stepper_type;

    integrate_const( stepper_type() , stuart_landau( 2.0 , 1.0 ) , x , 0.0 , 10.0 , dt , streaming_observer( cout ) );
    //]

    return 0;
}
