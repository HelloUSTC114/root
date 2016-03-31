// @(#)root/geom:$Id$
// Author: Mihaela Gheata   30/03/16

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TVirtualGeoConverter
\ingroup Geometry_classes

Abstract class for geometry converters
*/

#include "TVirtualGeoConverter.h"

#include "TROOT.h"
#include "TPluginManager.h"
#include "TGeoManager.h"

TVirtualGeoConverter  *TVirtualGeoConverter::fgGeoConverter = 0;

ClassImp(TVirtualGeoConverter)

////////////////////////////////////////////////////////////////////////////////
/// Geometry converter default constructor

TVirtualGeoConverter::TVirtualGeoConverter(TGeoManager *)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Geometry converter default destructor

TVirtualGeoConverter::~TVirtualGeoConverter()
{
   fgGeoConverter = 0;
}


////////////////////////////////////////////////////////////////////////////////
/// Static function returning a pointer to the current geometry converter.
/// The converter implements the ConvertGeometry function.
/// If the geometry converter does not exist a default converter is created.

TVirtualGeoConverter *TVirtualGeoConverter::Instance()
{
   // if no converter set yet, create a default converter via the PluginManager
   if (!fgGeoConverter) {
      TPluginHandler *h;
      if ((h = gROOT->GetPluginManager()->FindHandler("TVirtualGeoConverter"))) {
         if (h->LoadPlugin() == -1)
            return 0;
         fgGeoConverter = (TVirtualGeoConverter*)h->ExecPlugin(1,gGeoManager);
      }
   }
   return fgGeoConverter;
}

////////////////////////////////////////////////////////////////////////////////
/// Static function to set an alternative converter.

void TVirtualGeoConverter::SetConverter(const TVirtualGeoConverter *converter)
{
   fgGeoConverter = (TVirtualGeoConverter*)converter;
}
