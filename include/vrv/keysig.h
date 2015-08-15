
/////////////////////////////////////////////////////////////////////////////
// Name:        keysig.h
// Author:      Rodolfo Zitellini
// Created:     10/07/2012
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#ifndef __VRV_KEYSIG_H__
#define __VRV_KEYSIG_H__

#include "atts_shared.h"
#include "drawinglistinterface.h"
#include "layerelement.h"

namespace vrv {
    
class KeySigAttr;

//----------------------------------------------------------------------------
// KeySig
//----------------------------------------------------------------------------

/**
 * This class models the MEI <keySig> element.
 * Since it is unclear how to encode the logical key signature in keySig, an
 * internal representation is used (there is no equivalent of staffDef @key 
 * within keySig. Currently the @accid and @pname are used for this. The 
 * @pname store the value of the latest accidental, which is doubtfully the
 * expected use of it.
 * Two temporary method KeySig::ConvertToMei and KeySig::ConvertToInternal
 * are available for converting from and to the MEI representation to the 
 * internal (and reverse)
 */
class KeySig: public LayerElement, public KeySigDrawingInterface,
    public AttAccidental,
    public AttPitch
{
public:
    /**
     * @name Constructors, destructors, and other standard methods
     * Reset method reset all attribute classes.
     */
    ///@{
    KeySig();
    KeySig(int alterationNumber, data_ACCIDENTAL_EXPLICIT alterationType);
    KeySig( KeySigAttr *keySigAttr );
    void Init();
    virtual ~KeySig();
    virtual void Reset();
    virtual Object* Clone() { return new KeySig(*this); };
    virtual std::string GetClassName( ) { return "KeySig"; };
    virtual ClassId Is() { return KEY_SIG; };
    
    unsigned char GetAlterationAt(int pos);
    int GetOctave(unsigned char pitch, int clefId);
    
    /* Alteration number getter/setter */
    int GetAlterationNumber() { return m_alterationNumber; };
    void SetAlterationNumber(int alterationNumber) { m_alterationNumber = alterationNumber; };
    
    /* Alteration number getter/setter */
    data_ACCIDENTAL_EXPLICIT GetAlterationType() { return m_alterationType; };
    void SetAlterationType( data_ACCIDENTAL_EXPLICIT alterationType ) { m_alterationType = m_alterationType; };
    
    /* Temporary methods for turning @accid and @pitch into num_alter and alter */
    void ConvertToMei( );
    void ConvertToInternal( );
    
private:
    
public:
    
private:
    static data_PITCHNAME flats[];
    static data_PITCHNAME sharps[];
    static int octave_map[2][9][7];
    
    // This is temporary - it needs to be changed to libMEI atts
    int m_alterationNumber;
    data_ACCIDENTAL_EXPLICIT m_alterationType;
    
};
    
//----------------------------------------------------------------------------
// KeySigAttr
//----------------------------------------------------------------------------

/**
 * This class models the MEI @key attributes in scoreDef or staffDef elements.
 */
class KeySigAttr: public Object, public  KeySigDrawingInterface,
    public AttKeySigDefaultLog
{
public:
    /**
     * @name Constructors, destructors, reset and class name methods
     * Reset method reset all attribute classes
     */
    ///@{
    KeySigAttr();
    virtual ~KeySigAttr();
    virtual void Reset();
    virtual std::string GetClassName( ) { return "KeySigAttr"; };
    virtual ClassId Is() { return KEY_SIG_ATTR; };
    virtual Object* Clone() { return new KeySigAttr(*this); };
    ///@}
    
private:
    
public:
    
private:
    
};

} // namespace vrv    

#endif
