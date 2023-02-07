// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  bool ReplaceName( oCMobInter* inter ) {
    zSTRING name = inter->name;
    name = name.Upper();

    if ( zCVisual* visual = inter->GetVisual() ) {
      const string visualName = visual->GetVisualName();
      if ( visualName == "INNOS_NW_MISC_01.ASC" ) {
        inter->name = "MOBNAME_INNOS";
        inter->SetName( inter->name );
        return true;
      }

      if ( visualName == "INNOS_BELIAR_ADDON_01.ASC" ) {
        inter->name = "MOBNAME_ADDON_IDOL";
        inter->SetName( inter->name );
        return true;
      }

      if ( visualName == "INNOS_ADANOS_01.ASC" ) {
        inter->name = "MOBNAME_ADANOS";
        inter->SetName( inter->name );
        return true;
      }
    }

    if ( name == "SWITCH" && inter->GetScemeName() == "LEVER" ) {
      inter->name = "LEVER";
      inter->SetName( inter->name );
      return true;
    }

    return false;
  }

  void SetMobNames() {
    auto list = ogame->GetGameWorld()->voblist->GetNextInList();
    while ( list != nullptr ) {
      oCMOB* mob = list->GetData()->CastTo<oCMOB>();
      list = list->GetNextInList();

      if ( !mob )
        continue;

      oCMobInter* inter = mob->CastTo<oCMobInter>();

      if ( !inter )
        continue;

      if ( ReplaceName( inter ) )
        continue;

      if ( inter->GetName().Length() )
        continue;

      if ( inter->name.Length() ) {
        if ( inter->name.HasWord( " " ) )
          inter->name.Replace( " ", "_", true );

        inter->SetName( inter->name );
        continue;
      }

      zSTRING scemeName = inter->GetScemeName();

      if ( scemeName == "BOOK" )
        inter->name = "MOBNAME_BOOK";
      else if ( scemeName == "PAUKE" )
        inter->name = "MOBNAME_DRUM";
      else if ( scemeName == "ORCDRUM" )
        inter->name = "MOBNAME_ORCDRUM";
      else if ( scemeName == "TOUCHPLATE" || scemeName == "TURNSWITCH" )
        inter->name = "MOBNAME_SWITCH";
      else if ( scemeName == "VWHEEL" )
        inter->name = "MOBNAME_WHEEL";
      else if ( scemeName == "CHAIR" )
        inter->name = "MOBNAME_CHAIRALT";
      else if ( scemeName == "CHESTBIG" )
        inter->name = "MOBNAME_CHEST";
      else if ( scemeName == "BENCH" )
        inter->name = "MOBNAME_BENCH";

      if ( inter->name.Length() )
        inter->SetName( inter->name );
    }
  }
}