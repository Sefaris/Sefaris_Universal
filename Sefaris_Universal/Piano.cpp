// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  PianoManager::PianoManager() {
    int count = 0;

    while ( zCSoundFX* sfx = zsound->LoadSoundFX( soundPrefix + Z( count + 1 ) + ".WAV" ) ) {
      // Larger than 1 MB
      if ( sfx->GetResSizeBytes() > 1000000 ) {
        count++;
        sfx->Release();
      }
      else
        break;
    }

    soundCount = count;
  }

  oCMobInter* PianoManager::GetPiano() {
    auto list = ogame->GetGameWorld()->voblist->GetNextInList();
    while ( list != nullptr ) {
      oCMOB* mob = list->GetData()->CastTo<oCMOB>();
      list = list->GetNextInList();

      if ( !mob )
        continue;

      oCMobInter* inter = mob->CastTo<oCMobInter>();

      if ( !inter )
        continue;

      if ( inter->sceme == "KLAVIER" )
        return inter;
    }

    return nullptr;
  }

  void PianoManager::LoadBegin() {
    piano = nullptr;
  }

  void PianoManager::LoadEnd() {
    piano = GetPiano();
    soundHandler = Invalid;
  }

  zSTRING PianoManager::GetSoundName() {
    static Array<int> queue;

    if ( !queue.GetNum() )
      for ( int i = 0; i < soundCount; i++ )
        queue.Insert( i + 1 );

    int random = randomizer.Random( 0, queue.GetNum() );

    int songNum = queue[random];

    queue.Remove( songNum );

    return soundPrefix + Z( songNum ) + ".WAV";
  }

  void PianoManager::Loop() {
    if ( !ogame || !soundCount || !piano )
      return;

    auto world = ogame->GetGameWorld();
    if ( !world )
      return;

    if ( !piano->npcsCurrent || piano->homeWorld == nullptr ) {
      if ( soundHandler != Invalid && zsound->IsSoundActive( soundHandler ) )
        zsound->StopSound( soundHandler );

      soundHandler = Invalid;
      return;
    }

    if ( soundHandler != Invalid )
    {
      if ( zsound->IsSoundActive( soundHandler ) ) {
        zsound->UpdateSound3D( soundHandler, nullptr );
        return;
      }
      else
        soundHandler = Invalid;
    }

    if ( (int)player->GetDistanceToVob( *piano ) > 2500 )
      return;

    if ( zCSoundFX* sfx = zsound->LoadSoundFX( GetSoundName() ) ) {
      zCSoundSystem::zTSound3DParams params;
      params.SetDefaults();
      params.radius = 2500;
      soundHandler = zsound->PlaySound3D( sfx, piano, zSND_SLOT_NONE, &params );
      sfx->Release();
    }
  }
}