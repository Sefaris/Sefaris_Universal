// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  bool ReplaceName( oCMobInter* inter ) {
    zSTRING name = inter->name;
    name = name.Upper();

    if ( zCVisual* visual = inter->GetVisual() ) {
      const string visualName = visual->GetVisualName();
      if ( visualName == "CHESTSMALL_OCCHESTSMALLLOCKED.ASC" ) {
        inter->name = "MOBNAME_CHEST";
        inter->SetName( inter->name );
        return true;
      }
    }

    //if ( name == "SWITCH" && inter->GetScemeName() == "LEVER" ) {
    //  inter->name = "LEVER";
    //  inter->SetName( inter->name );
    //  return true;
    //}

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

      if ( scemeName == "CHESTSMALL" || scemeName == "CHESTBIG" )
        inter->name = "MOBNAME_CHEST";
      else if ( scemeName == "BENCH" )
        inter->name = "MOBNAME_BENCH";
      else if ( scemeName == "GERBBAUM" )
        inter->name = "MOBNAME_TAN";
      else if ( scemeName == "DOOR_FRONT" )
        inter->name = "MOBNAME_DOOR";
      else if ( scemeName == "CHAIR" )
        inter->name = "MOBNAME_CHAIR";
      else if ( scemeName == "CHAIR" )
        inter->name = "MOBNAME_CHAIR";
      else if ( scemeName == "BEDHIGH_FRONT" )
        inter->name = "MOBNAME_BED";
      else if ( scemeName == "THRONE" )
        inter->name = "MOBNAME_BED";
      //else if ( scemeName == "LADDER" )
      //  inter->name = "MOBNAME_LADDER";

      if ( inter->name.Length() )
        inter->SetName( inter->name );
    }
  }
}