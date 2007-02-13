/**
 *  @file SpeciesThermoInterpType.h
 *
 * $Author$
 * $Revision$
 * $Date$
 */

// Copyright 2001  California Institute of Technology

#include "speciesThermoTypes.h"

#ifndef CT_SPECIESTHERMOINTERPTYPE_H
#define CT_SPECIESTHERMOINTERPTYPE_H

namespace Cantera {

  /**
   * Virtual Base class for individual species reference state
   * themodynamic managers. This differs from the SpeciesThermo virtual
   * base class in the sense that this class is meant to handle only
   * one species. The speciesThermo class is meant to handle the 
   * calculation of all the species (or a large subset) in a phase.
   *
   * One key feature is that the update routines use the same
   * form as the update routines in the speciesThermo class. They update
   * into a vector of cp_R, s_R, and H_R that spans all of the species in 
   * a phase. Therefore, this class must carry along a species index into that
   * vector.
   *
   * @ingroup spthermo
   */    
  class SpeciesThermoInterpType {

  public:
    
    //! Constructor
    SpeciesThermoInterpType() {};

    //! Destructor
    virtual ~SpeciesThermoInterpType() {};

    //! duplicator
    virtual SpeciesThermoInterpType * 
    duplMyselfAsSpeciesThermoInterpType() const = 0;
       

    //! Returns the minimum temperature that the thermo
    //! parameterization is valid
    virtual doublereal minTemp() const = 0;

    //! Returns the maximum temperature that the thermo
    //! parameterization is valid
    virtual doublereal maxTemp() const = 0;

    //! Returns the reference pressure (Pa)
    virtual doublereal refPressure() const = 0;

    //! Returns an integer representing the type of parameterization
    virtual int reportType() const = 0;
  
    //! Update the properties for this species, given a temperature polynomial
    /*!
     * This method is calledwith a pointer to an array containing the functions of
     * temperature needed by this  parameterization, and three pointers to arrays where the
     * computed property values should be written. This method updates only one value in
     * each array.
     *
     * Temperature Polynomial:
     *  tt[0] = t;
     *  tt[1] = t*t;
     *  tt[2] = m_t[1]*t;
     *  tt[3] = m_t[2]*t;
     *  tt[4] = 1.0/t;
     *  tt[5] = std::log(t);
     *
     * @param tempPoly  vector of temperature polynomials
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     */
    virtual void updateProperties(const doublereal* tempPoly, 
				  doublereal* cp_R, doublereal* h_RT,
				  doublereal* s_R) const = 0;

    //! Compute the reference-state property of one species
    /*!
     * Given temperature T in K, this method updates the values of
     * the non-dimensional heat capacity at constant pressure,
     * enthalpy, and entropy, at the reference pressure, Pref
     * of one of the species. The species index is used
     * to reference into the cp_R, h_RT, and s_R arrays.
     *
     * @param temp    Temperature (Kelvin)
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     */
    virtual void updatePropertiesTemp(const doublereal temp, 
				      doublereal* cp_R,
				      doublereal* h_RT,
				      doublereal* s_R) const = 0;
    
    //!This utility function reports back the type of 
    //! parameterization and all of the parameters for the 
    //! species, index.
    /*!
     * All parameters are output variables
     *
     * @param index     Species index
     * @param type      Integer type of the standard type
     * @param minTemp   output - Minimum temperature
     * @param maxTemp   output - Maximum temperature
     * @param refPressure output - reference pressure (Pa).
     * @param coeffs    Vector of coefficients used to set the
     *                  parameters for the standard state.
     *
     * @todo should be a const function.
     */
    virtual void reportParameters(int &index, int &type,
				  doublereal &minTemp, doublereal &maxTemp,
				  doublereal &refPressure,
				  doublereal* const coeffs) const = 0;

    //! Modify parameters for the standard state
    /*!
     * @param coeffs   Vector of coefficients used to set the
     *                 parameters for the standard state.
     */
    virtual void modifyParameters(doublereal* coeffs) {}

  };

}

#endif

