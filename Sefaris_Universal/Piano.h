// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
  class PianoManager
  {
  private:
    const zSTRING soundPrefix = "SND_PIANO_";
    int soundCount;

    oCMobInter* piano = nullptr;
    int soundHandler = Invalid;

    oCMobInter* GetPiano();
    zSTRING GetSoundName();

  public:
    void LoadEnd();
    void LoadBegin();
    void Loop();
    PianoManager();
  };

  PianoManager* pianoManager;
}