// $Id: TG4SteppingAction.h,v 1.4 2005/09/01 10:04:32 brun Exp $
/// \ingroup event
//
/// \class TG4SteppingAction
/// \brief Actions at each step
/// 
/// This class ensures the additional call to the sensitive detector
/// when track crosses a geometrical boundary.
/// It also enables to define a maximum number of steps
/// and takes care of stopping of a track when this number
/// is reached.
///
/// Author: I.Hrivnacova

#ifndef TG4_STEPPING_ACTION_H
#define TG4_STEPPING_ACTION_H

#include "TG4SteppingActionMessenger.h"

#include <G4UserSteppingAction.hh>

#include <globals.hh>

class G4Track;
class G4Step;

class TG4SteppingAction : public G4UserSteppingAction 
{
  enum { 
    kMaxNofSteps = 30000,
    kMaxNofLoopSteps = 5
  };

  public:
    TG4SteppingAction();
    virtual ~TG4SteppingAction();
   
    // static access method
    static TG4SteppingAction* Instance();

    // methods
    virtual void SteppingAction(const G4Step* step);
                  // the following method should not
                  // be overwritten in a derived class
    virtual void UserSteppingAction(const G4Step* step);

    // set methods
    void SetLoopVerboseLevel(G4int level);
    void SetMaxNofSteps(G4int number);

    // get methods
    G4int GetLoopVerboseLevel() const;
    G4int GetMaxNofSteps() const;

  protected:
    // methods
    void PrintTrackInfo(const G4Track* track) const;

  private:
    TG4SteppingAction(const TG4SteppingAction& right);
    TG4SteppingAction& operator=(const TG4SteppingAction& right);

    // static data members
    static TG4SteppingAction*   fgInstance; //this instance

    // data members
    TG4SteppingActionMessenger  fMessenger; //messenger    
    G4int  fMaxNofSteps;          //max number of steps allowed
    G4int  fStandardVerboseLevel; //standard tracking verbose level
    G4int  fLoopVerboseLevel;     //tracking verbose level                                           //for looping particles
                                  //for looping particles
    G4int  fLoopStepCounter;      //loop steps counter    

};

// inline methods

inline TG4SteppingAction* TG4SteppingAction::Instance() { 
  /// Return this instance
  return fgInstance; 
}

inline void TG4SteppingAction::SteppingAction(const G4Step* /*step*/) {
  /// Dummy stepping action that can be overriden
  /// in a user defined class
}  

inline void TG4SteppingAction::SetLoopVerboseLevel(G4int level) { 
  /// Set loop verbose level (applied when a track is looping) 
  fLoopVerboseLevel = level; 
}

inline void TG4SteppingAction::SetMaxNofSteps(G4int number) { 
  /// Set maximum number of steps allowed 
  fMaxNofSteps = number; 
}

inline G4int TG4SteppingAction::GetMaxNofSteps() const { 
  /// Get maximum number of steps allowed 
  return fMaxNofSteps; 
}

inline G4int TG4SteppingAction::GetLoopVerboseLevel() const { 
  /// Get loop verbose level (applied when a track is looping) 
  return fLoopVerboseLevel; 
}

#endif //TG4_STEPPING_ACTION_H
