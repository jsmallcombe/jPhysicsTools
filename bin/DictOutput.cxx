// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME bindIDictOutput

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/james_LeeNucleusExtend.h"
#include "include/james_nuclear_data_gui.h"
#include "include/james_nuclear_data_ob.h"
#include "include/james_fission.h"
#include "include/james_root_maths.h"
#include "include/james_legendre.h"
#include "include/james_target.h"
#include "include/james_physics.h"
#include "include/james_physhist_format.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *cNucleusInh_Dictionary();
   static void cNucleusInh_TClassManip(TClass*);
   static void *new_cNucleusInh(void *p = 0);
   static void *newArray_cNucleusInh(Long_t size, void *p);
   static void delete_cNucleusInh(void *p);
   static void deleteArray_cNucleusInh(void *p);
   static void destruct_cNucleusInh(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cNucleusInh*)
   {
      ::cNucleusInh *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::cNucleusInh));
      static ::ROOT::TGenericClassInfo 
         instance("cNucleusInh", "james_LeeNucleusExtend.h", 26,
                  typeid(::cNucleusInh), DefineBehavior(ptr, ptr),
                  &cNucleusInh_Dictionary, isa_proxy, 4,
                  sizeof(::cNucleusInh) );
      instance.SetNew(&new_cNucleusInh);
      instance.SetNewArray(&newArray_cNucleusInh);
      instance.SetDelete(&delete_cNucleusInh);
      instance.SetDeleteArray(&deleteArray_cNucleusInh);
      instance.SetDestructor(&destruct_cNucleusInh);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cNucleusInh*)
   {
      return GenerateInitInstanceLocal((::cNucleusInh*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::cNucleusInh*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *cNucleusInh_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::cNucleusInh*)0x0)->GetClass();
      cNucleusInh_TClassManip(theClass);
   return theClass;
   }

   static void cNucleusInh_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_LeeNucleusExtend.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *NucDatumSpecifier_Dictionary();
   static void NucDatumSpecifier_TClassManip(TClass*);
   static void *new_NucDatumSpecifier(void *p = 0);
   static void *newArray_NucDatumSpecifier(Long_t size, void *p);
   static void delete_NucDatumSpecifier(void *p);
   static void deleteArray_NucDatumSpecifier(void *p);
   static void destruct_NucDatumSpecifier(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NucDatumSpecifier*)
   {
      ::NucDatumSpecifier *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::NucDatumSpecifier));
      static ::ROOT::TGenericClassInfo 
         instance("NucDatumSpecifier", "james_LeeNucleusExtend.h", 64,
                  typeid(::NucDatumSpecifier), DefineBehavior(ptr, ptr),
                  &NucDatumSpecifier_Dictionary, isa_proxy, 4,
                  sizeof(::NucDatumSpecifier) );
      instance.SetNew(&new_NucDatumSpecifier);
      instance.SetNewArray(&newArray_NucDatumSpecifier);
      instance.SetDelete(&delete_NucDatumSpecifier);
      instance.SetDeleteArray(&deleteArray_NucDatumSpecifier);
      instance.SetDestructor(&destruct_NucDatumSpecifier);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NucDatumSpecifier*)
   {
      return GenerateInitInstanceLocal((::NucDatumSpecifier*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::NucDatumSpecifier*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *NucDatumSpecifier_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::NucDatumSpecifier*)0x0)->GetClass();
      NucDatumSpecifier_TClassManip(theClass);
   return theClass;
   }

   static void NucDatumSpecifier_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_LeeNucleusExtend.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *legendre_polynomials_Dictionary();
   static void legendre_polynomials_TClassManip(TClass*);
   static void *new_legendre_polynomials(void *p = 0);
   static void *newArray_legendre_polynomials(Long_t size, void *p);
   static void delete_legendre_polynomials(void *p);
   static void deleteArray_legendre_polynomials(void *p);
   static void destruct_legendre_polynomials(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::legendre_polynomials*)
   {
      ::legendre_polynomials *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::legendre_polynomials));
      static ::ROOT::TGenericClassInfo 
         instance("legendre_polynomials", "james_legendre.h", 28,
                  typeid(::legendre_polynomials), DefineBehavior(ptr, ptr),
                  &legendre_polynomials_Dictionary, isa_proxy, 4,
                  sizeof(::legendre_polynomials) );
      instance.SetNew(&new_legendre_polynomials);
      instance.SetNewArray(&newArray_legendre_polynomials);
      instance.SetDelete(&delete_legendre_polynomials);
      instance.SetDeleteArray(&deleteArray_legendre_polynomials);
      instance.SetDestructor(&destruct_legendre_polynomials);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::legendre_polynomials*)
   {
      return GenerateInitInstanceLocal((::legendre_polynomials*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::legendre_polynomials*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *legendre_polynomials_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::legendre_polynomials*)0x0)->GetClass();
      legendre_polynomials_TClassManip(theClass);
   return theClass;
   }

   static void legendre_polynomials_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_legendre.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *spherical_harmonic_Dictionary();
   static void spherical_harmonic_TClassManip(TClass*);
   static void *new_spherical_harmonic(void *p = 0);
   static void *newArray_spherical_harmonic(Long_t size, void *p);
   static void delete_spherical_harmonic(void *p);
   static void deleteArray_spherical_harmonic(void *p);
   static void destruct_spherical_harmonic(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::spherical_harmonic*)
   {
      ::spherical_harmonic *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::spherical_harmonic));
      static ::ROOT::TGenericClassInfo 
         instance("spherical_harmonic", "james_legendre.h", 54,
                  typeid(::spherical_harmonic), DefineBehavior(ptr, ptr),
                  &spherical_harmonic_Dictionary, isa_proxy, 4,
                  sizeof(::spherical_harmonic) );
      instance.SetNew(&new_spherical_harmonic);
      instance.SetNewArray(&newArray_spherical_harmonic);
      instance.SetDelete(&delete_spherical_harmonic);
      instance.SetDeleteArray(&deleteArray_spherical_harmonic);
      instance.SetDestructor(&destruct_spherical_harmonic);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::spherical_harmonic*)
   {
      return GenerateInitInstanceLocal((::spherical_harmonic*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::spherical_harmonic*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *spherical_harmonic_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::spherical_harmonic*)0x0)->GetClass();
      spherical_harmonic_TClassManip(theClass);
   return theClass;
   }

   static void spherical_harmonic_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_legendre.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *gamma_dist_Dictionary();
   static void gamma_dist_TClassManip(TClass*);
   static void *new_gamma_dist(void *p = 0);
   static void *newArray_gamma_dist(Long_t size, void *p);
   static void delete_gamma_dist(void *p);
   static void deleteArray_gamma_dist(void *p);
   static void destruct_gamma_dist(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::gamma_dist*)
   {
      ::gamma_dist *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::gamma_dist));
      static ::ROOT::TGenericClassInfo 
         instance("gamma_dist", "james_legendre.h", 85,
                  typeid(::gamma_dist), DefineBehavior(ptr, ptr),
                  &gamma_dist_Dictionary, isa_proxy, 4,
                  sizeof(::gamma_dist) );
      instance.SetNew(&new_gamma_dist);
      instance.SetNewArray(&newArray_gamma_dist);
      instance.SetDelete(&delete_gamma_dist);
      instance.SetDeleteArray(&deleteArray_gamma_dist);
      instance.SetDestructor(&destruct_gamma_dist);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::gamma_dist*)
   {
      return GenerateInitInstanceLocal((::gamma_dist*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::gamma_dist*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *gamma_dist_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::gamma_dist*)0x0)->GetClass();
      gamma_dist_TClassManip(theClass);
   return theClass;
   }

   static void gamma_dist_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_legendre.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataSlicer(void *p = 0);
   static void *newArray_LiveDataSlicer(Long_t size, void *p);
   static void delete_LiveDataSlicer(void *p);
   static void deleteArray_LiveDataSlicer(void *p);
   static void destruct_LiveDataSlicer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataSlicer*)
   {
      ::LiveDataSlicer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataSlicer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataSlicer", ::LiveDataSlicer::Class_Version(), "james_nuclear_data_gui.h", 58,
                  typeid(::LiveDataSlicer), DefineBehavior(ptr, ptr),
                  &::LiveDataSlicer::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataSlicer) );
      instance.SetNew(&new_LiveDataSlicer);
      instance.SetNewArray(&newArray_LiveDataSlicer);
      instance.SetDelete(&delete_LiveDataSlicer);
      instance.SetDeleteArray(&deleteArray_LiveDataSlicer);
      instance.SetDestructor(&destruct_LiveDataSlicer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataSlicer*)
   {
      return GenerateInitInstanceLocal((::LiveDataSlicer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataSlicer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataAdder(void *p = 0);
   static void *newArray_LiveDataAdder(Long_t size, void *p);
   static void delete_LiveDataAdder(void *p);
   static void deleteArray_LiveDataAdder(void *p);
   static void destruct_LiveDataAdder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataAdder*)
   {
      ::LiveDataAdder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataAdder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataAdder", ::LiveDataAdder::Class_Version(), "james_nuclear_data_gui.h", 94,
                  typeid(::LiveDataAdder), DefineBehavior(ptr, ptr),
                  &::LiveDataAdder::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataAdder) );
      instance.SetNew(&new_LiveDataAdder);
      instance.SetNewArray(&newArray_LiveDataAdder);
      instance.SetDelete(&delete_LiveDataAdder);
      instance.SetDeleteArray(&deleteArray_LiveDataAdder);
      instance.SetDestructor(&destruct_LiveDataAdder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataAdder*)
   {
      return GenerateInitInstanceLocal((::LiveDataAdder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataAdder*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataAdderLevelSelect(void *p = 0);
   static void *newArray_LiveDataAdderLevelSelect(Long_t size, void *p);
   static void delete_LiveDataAdderLevelSelect(void *p);
   static void deleteArray_LiveDataAdderLevelSelect(void *p);
   static void destruct_LiveDataAdderLevelSelect(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataAdderLevelSelect*)
   {
      ::LiveDataAdderLevelSelect *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataAdderLevelSelect >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataAdderLevelSelect", ::LiveDataAdderLevelSelect::Class_Version(), "james_nuclear_data_gui.h", 120,
                  typeid(::LiveDataAdderLevelSelect), DefineBehavior(ptr, ptr),
                  &::LiveDataAdderLevelSelect::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataAdderLevelSelect) );
      instance.SetNew(&new_LiveDataAdderLevelSelect);
      instance.SetNewArray(&newArray_LiveDataAdderLevelSelect);
      instance.SetDelete(&delete_LiveDataAdderLevelSelect);
      instance.SetDeleteArray(&deleteArray_LiveDataAdderLevelSelect);
      instance.SetDestructor(&destruct_LiveDataAdderLevelSelect);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataAdderLevelSelect*)
   {
      return GenerateInitInstanceLocal((::LiveDataAdderLevelSelect*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataAdderLevelSelect*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *PadScanData_Dictionary();
   static void PadScanData_TClassManip(TClass*);
   static void *new_PadScanData(void *p = 0);
   static void *newArray_PadScanData(Long_t size, void *p);
   static void delete_PadScanData(void *p);
   static void deleteArray_PadScanData(void *p);
   static void destruct_PadScanData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PadScanData*)
   {
      ::PadScanData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PadScanData));
      static ::ROOT::TGenericClassInfo 
         instance("PadScanData", "james_nuclear_data_gui.h", 139,
                  typeid(::PadScanData), DefineBehavior(ptr, ptr),
                  &PadScanData_Dictionary, isa_proxy, 4,
                  sizeof(::PadScanData) );
      instance.SetNew(&new_PadScanData);
      instance.SetNewArray(&newArray_PadScanData);
      instance.SetDelete(&delete_PadScanData);
      instance.SetDeleteArray(&deleteArray_PadScanData);
      instance.SetDestructor(&destruct_PadScanData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PadScanData*)
   {
      return GenerateInitInstanceLocal((::PadScanData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PadScanData*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PadScanData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PadScanData*)0x0)->GetClass();
      PadScanData_TClassManip(theClass);
   return theClass;
   }

   static void PadScanData_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_nuclear_data_gui.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataGUIentry(void *p = 0);
   static void *newArray_LiveDataGUIentry(Long_t size, void *p);
   static void delete_LiveDataGUIentry(void *p);
   static void deleteArray_LiveDataGUIentry(void *p);
   static void destruct_LiveDataGUIentry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataGUIentry*)
   {
      ::LiveDataGUIentry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataGUIentry >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataGUIentry", ::LiveDataGUIentry::Class_Version(), "james_nuclear_data_gui.h", 184,
                  typeid(::LiveDataGUIentry), DefineBehavior(ptr, ptr),
                  &::LiveDataGUIentry::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataGUIentry) );
      instance.SetNew(&new_LiveDataGUIentry);
      instance.SetNewArray(&newArray_LiveDataGUIentry);
      instance.SetDelete(&delete_LiveDataGUIentry);
      instance.SetDeleteArray(&deleteArray_LiveDataGUIentry);
      instance.SetDestructor(&destruct_LiveDataGUIentry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataGUIentry*)
   {
      return GenerateInitInstanceLocal((::LiveDataGUIentry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataGUIentry*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataGUIStyleControl(void *p = 0);
   static void *newArray_LiveDataGUIStyleControl(Long_t size, void *p);
   static void delete_LiveDataGUIStyleControl(void *p);
   static void deleteArray_LiveDataGUIStyleControl(void *p);
   static void destruct_LiveDataGUIStyleControl(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataGUIStyleControl*)
   {
      ::LiveDataGUIStyleControl *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataGUIStyleControl >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataGUIStyleControl", ::LiveDataGUIStyleControl::Class_Version(), "james_nuclear_data_gui.h", 204,
                  typeid(::LiveDataGUIStyleControl), DefineBehavior(ptr, ptr),
                  &::LiveDataGUIStyleControl::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataGUIStyleControl) );
      instance.SetNew(&new_LiveDataGUIStyleControl);
      instance.SetNewArray(&newArray_LiveDataGUIStyleControl);
      instance.SetDelete(&delete_LiveDataGUIStyleControl);
      instance.SetDeleteArray(&deleteArray_LiveDataGUIStyleControl);
      instance.SetDestructor(&destruct_LiveDataGUIStyleControl);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataGUIStyleControl*)
   {
      return GenerateInitInstanceLocal((::LiveDataGUIStyleControl*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataGUIStyleControl*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LiveDataAdjuster(void *p = 0);
   static void *newArray_LiveDataAdjuster(Long_t size, void *p);
   static void delete_LiveDataAdjuster(void *p);
   static void deleteArray_LiveDataAdjuster(void *p);
   static void destruct_LiveDataAdjuster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LiveDataAdjuster*)
   {
      ::LiveDataAdjuster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LiveDataAdjuster >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LiveDataAdjuster", ::LiveDataAdjuster::Class_Version(), "james_nuclear_data_gui.h", 220,
                  typeid(::LiveDataAdjuster), DefineBehavior(ptr, ptr),
                  &::LiveDataAdjuster::Dictionary, isa_proxy, 4,
                  sizeof(::LiveDataAdjuster) );
      instance.SetNew(&new_LiveDataAdjuster);
      instance.SetNewArray(&newArray_LiveDataAdjuster);
      instance.SetDelete(&delete_LiveDataAdjuster);
      instance.SetDeleteArray(&deleteArray_LiveDataAdjuster);
      instance.SetDestructor(&destruct_LiveDataAdjuster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LiveDataAdjuster*)
   {
      return GenerateInitInstanceLocal((::LiveDataAdjuster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LiveDataAdjuster*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *nuclear_data_ob_Dictionary();
   static void nuclear_data_ob_TClassManip(TClass*);
   static void *new_nuclear_data_ob(void *p = 0);
   static void *newArray_nuclear_data_ob(Long_t size, void *p);
   static void delete_nuclear_data_ob(void *p);
   static void deleteArray_nuclear_data_ob(void *p);
   static void destruct_nuclear_data_ob(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::nuclear_data_ob*)
   {
      ::nuclear_data_ob *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::nuclear_data_ob));
      static ::ROOT::TGenericClassInfo 
         instance("nuclear_data_ob", "james_nuclear_data_ob.h", 78,
                  typeid(::nuclear_data_ob), DefineBehavior(ptr, ptr),
                  &nuclear_data_ob_Dictionary, isa_proxy, 4,
                  sizeof(::nuclear_data_ob) );
      instance.SetNew(&new_nuclear_data_ob);
      instance.SetNewArray(&newArray_nuclear_data_ob);
      instance.SetDelete(&delete_nuclear_data_ob);
      instance.SetDeleteArray(&deleteArray_nuclear_data_ob);
      instance.SetDestructor(&destruct_nuclear_data_ob);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::nuclear_data_ob*)
   {
      return GenerateInitInstanceLocal((::nuclear_data_ob*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::nuclear_data_ob*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *nuclear_data_ob_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::nuclear_data_ob*)0x0)->GetClass();
      nuclear_data_ob_TClassManip(theClass);
   return theClass;
   }

   static void nuclear_data_ob_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_nuclear_data_ob.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *cNucleusIterator_Dictionary();
   static void cNucleusIterator_TClassManip(TClass*);
   static void *new_cNucleusIterator(void *p = 0);
   static void *newArray_cNucleusIterator(Long_t size, void *p);
   static void delete_cNucleusIterator(void *p);
   static void deleteArray_cNucleusIterator(void *p);
   static void destruct_cNucleusIterator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cNucleusIterator*)
   {
      ::cNucleusIterator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::cNucleusIterator));
      static ::ROOT::TGenericClassInfo 
         instance("cNucleusIterator", "james_nuclear_data_ob.h", 300,
                  typeid(::cNucleusIterator), DefineBehavior(ptr, ptr),
                  &cNucleusIterator_Dictionary, isa_proxy, 4,
                  sizeof(::cNucleusIterator) );
      instance.SetNew(&new_cNucleusIterator);
      instance.SetNewArray(&newArray_cNucleusIterator);
      instance.SetDelete(&delete_cNucleusIterator);
      instance.SetDeleteArray(&deleteArray_cNucleusIterator);
      instance.SetDestructor(&destruct_cNucleusIterator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cNucleusIterator*)
   {
      return GenerateInitInstanceLocal((::cNucleusIterator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::cNucleusIterator*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *cNucleusIterator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::cNucleusIterator*)0x0)->GetClass();
      cNucleusIterator_TClassManip(theClass);
   return theClass;
   }

   static void cNucleusIterator_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_nuclear_data_ob.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *target_Dictionary();
   static void target_TClassManip(TClass*);
   static void *new_target(void *p = 0);
   static void *newArray_target(Long_t size, void *p);
   static void delete_target(void *p);
   static void deleteArray_target(void *p);
   static void destruct_target(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::target*)
   {
      ::target *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::target));
      static ::ROOT::TGenericClassInfo 
         instance("target", "james_target.h", 66,
                  typeid(::target), DefineBehavior(ptr, ptr),
                  &target_Dictionary, isa_proxy, 4,
                  sizeof(::target) );
      instance.SetNew(&new_target);
      instance.SetNewArray(&newArray_target);
      instance.SetDelete(&delete_target);
      instance.SetDeleteArray(&deleteArray_target);
      instance.SetDestructor(&destruct_target);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::target*)
   {
      return GenerateInitInstanceLocal((::target*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::target*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *target_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::target*)0x0)->GetClass();
      target_TClassManip(theClass);
   return theClass;
   }

   static void target_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_target.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *cNucleus_Dictionary();
   static void cNucleus_TClassManip(TClass*);
   static void *new_cNucleus(void *p = 0);
   static void *newArray_cNucleus(Long_t size, void *p);
   static void delete_cNucleus(void *p);
   static void deleteArray_cNucleus(void *p);
   static void destruct_cNucleus(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cNucleus*)
   {
      ::cNucleus *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::cNucleus));
      static ::ROOT::TGenericClassInfo 
         instance("cNucleus", "LeeNucleus.h", 24,
                  typeid(::cNucleus), DefineBehavior(ptr, ptr),
                  &cNucleus_Dictionary, isa_proxy, 4,
                  sizeof(::cNucleus) );
      instance.SetNew(&new_cNucleus);
      instance.SetNewArray(&newArray_cNucleus);
      instance.SetDelete(&delete_cNucleus);
      instance.SetDeleteArray(&deleteArray_cNucleus);
      instance.SetDestructor(&destruct_cNucleus);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cNucleus*)
   {
      return GenerateInitInstanceLocal((::cNucleus*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::cNucleus*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *cNucleus_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::cNucleus*)0x0)->GetClass();
      cNucleus_TClassManip(theClass);
   return theClass;
   }

   static void cNucleus_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/LeeNucleus.h");
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr LiveDataSlicer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataSlicer::Class_Name()
{
   return "LiveDataSlicer";
}

//______________________________________________________________________________
const char *LiveDataSlicer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataSlicer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataSlicer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataSlicer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataSlicer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataSlicer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataSlicer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataSlicer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiveDataAdder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataAdder::Class_Name()
{
   return "LiveDataAdder";
}

//______________________________________________________________________________
const char *LiveDataAdder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataAdder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataAdder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataAdder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiveDataAdderLevelSelect::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataAdderLevelSelect::Class_Name()
{
   return "LiveDataAdderLevelSelect";
}

//______________________________________________________________________________
const char *LiveDataAdderLevelSelect::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdderLevelSelect*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataAdderLevelSelect::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdderLevelSelect*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataAdderLevelSelect::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdderLevelSelect*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataAdderLevelSelect::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdderLevelSelect*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiveDataGUIentry::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataGUIentry::Class_Name()
{
   return "LiveDataGUIentry";
}

//______________________________________________________________________________
const char *LiveDataGUIentry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIentry*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataGUIentry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIentry*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataGUIentry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIentry*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataGUIentry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIentry*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiveDataGUIStyleControl::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataGUIStyleControl::Class_Name()
{
   return "LiveDataGUIStyleControl";
}

//______________________________________________________________________________
const char *LiveDataGUIStyleControl::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIStyleControl*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataGUIStyleControl::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIStyleControl*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataGUIStyleControl::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIStyleControl*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataGUIStyleControl::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataGUIStyleControl*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LiveDataAdjuster::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LiveDataAdjuster::Class_Name()
{
   return "LiveDataAdjuster";
}

//______________________________________________________________________________
const char *LiveDataAdjuster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdjuster*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LiveDataAdjuster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdjuster*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LiveDataAdjuster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdjuster*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LiveDataAdjuster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LiveDataAdjuster*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cNucleusInh(void *p) {
      return  p ? new(p) ::cNucleusInh : new ::cNucleusInh;
   }
   static void *newArray_cNucleusInh(Long_t nElements, void *p) {
      return p ? new(p) ::cNucleusInh[nElements] : new ::cNucleusInh[nElements];
   }
   // Wrapper around operator delete
   static void delete_cNucleusInh(void *p) {
      delete ((::cNucleusInh*)p);
   }
   static void deleteArray_cNucleusInh(void *p) {
      delete [] ((::cNucleusInh*)p);
   }
   static void destruct_cNucleusInh(void *p) {
      typedef ::cNucleusInh current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cNucleusInh

namespace ROOT {
   // Wrappers around operator new
   static void *new_NucDatumSpecifier(void *p) {
      return  p ? new(p) ::NucDatumSpecifier : new ::NucDatumSpecifier;
   }
   static void *newArray_NucDatumSpecifier(Long_t nElements, void *p) {
      return p ? new(p) ::NucDatumSpecifier[nElements] : new ::NucDatumSpecifier[nElements];
   }
   // Wrapper around operator delete
   static void delete_NucDatumSpecifier(void *p) {
      delete ((::NucDatumSpecifier*)p);
   }
   static void deleteArray_NucDatumSpecifier(void *p) {
      delete [] ((::NucDatumSpecifier*)p);
   }
   static void destruct_NucDatumSpecifier(void *p) {
      typedef ::NucDatumSpecifier current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::NucDatumSpecifier

namespace ROOT {
   // Wrappers around operator new
   static void *new_legendre_polynomials(void *p) {
      return  p ? new(p) ::legendre_polynomials : new ::legendre_polynomials;
   }
   static void *newArray_legendre_polynomials(Long_t nElements, void *p) {
      return p ? new(p) ::legendre_polynomials[nElements] : new ::legendre_polynomials[nElements];
   }
   // Wrapper around operator delete
   static void delete_legendre_polynomials(void *p) {
      delete ((::legendre_polynomials*)p);
   }
   static void deleteArray_legendre_polynomials(void *p) {
      delete [] ((::legendre_polynomials*)p);
   }
   static void destruct_legendre_polynomials(void *p) {
      typedef ::legendre_polynomials current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::legendre_polynomials

namespace ROOT {
   // Wrappers around operator new
   static void *new_spherical_harmonic(void *p) {
      return  p ? new(p) ::spherical_harmonic : new ::spherical_harmonic;
   }
   static void *newArray_spherical_harmonic(Long_t nElements, void *p) {
      return p ? new(p) ::spherical_harmonic[nElements] : new ::spherical_harmonic[nElements];
   }
   // Wrapper around operator delete
   static void delete_spherical_harmonic(void *p) {
      delete ((::spherical_harmonic*)p);
   }
   static void deleteArray_spherical_harmonic(void *p) {
      delete [] ((::spherical_harmonic*)p);
   }
   static void destruct_spherical_harmonic(void *p) {
      typedef ::spherical_harmonic current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::spherical_harmonic

namespace ROOT {
   // Wrappers around operator new
   static void *new_gamma_dist(void *p) {
      return  p ? new(p) ::gamma_dist : new ::gamma_dist;
   }
   static void *newArray_gamma_dist(Long_t nElements, void *p) {
      return p ? new(p) ::gamma_dist[nElements] : new ::gamma_dist[nElements];
   }
   // Wrapper around operator delete
   static void delete_gamma_dist(void *p) {
      delete ((::gamma_dist*)p);
   }
   static void deleteArray_gamma_dist(void *p) {
      delete [] ((::gamma_dist*)p);
   }
   static void destruct_gamma_dist(void *p) {
      typedef ::gamma_dist current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::gamma_dist

//______________________________________________________________________________
void LiveDataSlicer::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataSlicer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataSlicer::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataSlicer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataSlicer(void *p) {
      return  p ? new(p) ::LiveDataSlicer : new ::LiveDataSlicer;
   }
   static void *newArray_LiveDataSlicer(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataSlicer[nElements] : new ::LiveDataSlicer[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataSlicer(void *p) {
      delete ((::LiveDataSlicer*)p);
   }
   static void deleteArray_LiveDataSlicer(void *p) {
      delete [] ((::LiveDataSlicer*)p);
   }
   static void destruct_LiveDataSlicer(void *p) {
      typedef ::LiveDataSlicer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataSlicer

//______________________________________________________________________________
void LiveDataAdder::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataAdder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataAdder::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataAdder::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataAdder(void *p) {
      return  p ? new(p) ::LiveDataAdder : new ::LiveDataAdder;
   }
   static void *newArray_LiveDataAdder(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataAdder[nElements] : new ::LiveDataAdder[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataAdder(void *p) {
      delete ((::LiveDataAdder*)p);
   }
   static void deleteArray_LiveDataAdder(void *p) {
      delete [] ((::LiveDataAdder*)p);
   }
   static void destruct_LiveDataAdder(void *p) {
      typedef ::LiveDataAdder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataAdder

//______________________________________________________________________________
void LiveDataAdderLevelSelect::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataAdderLevelSelect.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataAdderLevelSelect::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataAdderLevelSelect::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataAdderLevelSelect(void *p) {
      return  p ? new(p) ::LiveDataAdderLevelSelect : new ::LiveDataAdderLevelSelect;
   }
   static void *newArray_LiveDataAdderLevelSelect(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataAdderLevelSelect[nElements] : new ::LiveDataAdderLevelSelect[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataAdderLevelSelect(void *p) {
      delete ((::LiveDataAdderLevelSelect*)p);
   }
   static void deleteArray_LiveDataAdderLevelSelect(void *p) {
      delete [] ((::LiveDataAdderLevelSelect*)p);
   }
   static void destruct_LiveDataAdderLevelSelect(void *p) {
      typedef ::LiveDataAdderLevelSelect current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataAdderLevelSelect

namespace ROOT {
   // Wrappers around operator new
   static void *new_PadScanData(void *p) {
      return  p ? new(p) ::PadScanData : new ::PadScanData;
   }
   static void *newArray_PadScanData(Long_t nElements, void *p) {
      return p ? new(p) ::PadScanData[nElements] : new ::PadScanData[nElements];
   }
   // Wrapper around operator delete
   static void delete_PadScanData(void *p) {
      delete ((::PadScanData*)p);
   }
   static void deleteArray_PadScanData(void *p) {
      delete [] ((::PadScanData*)p);
   }
   static void destruct_PadScanData(void *p) {
      typedef ::PadScanData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PadScanData

//______________________________________________________________________________
void LiveDataGUIentry::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataGUIentry.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataGUIentry::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataGUIentry::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataGUIentry(void *p) {
      return  p ? new(p) ::LiveDataGUIentry : new ::LiveDataGUIentry;
   }
   static void *newArray_LiveDataGUIentry(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataGUIentry[nElements] : new ::LiveDataGUIentry[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataGUIentry(void *p) {
      delete ((::LiveDataGUIentry*)p);
   }
   static void deleteArray_LiveDataGUIentry(void *p) {
      delete [] ((::LiveDataGUIentry*)p);
   }
   static void destruct_LiveDataGUIentry(void *p) {
      typedef ::LiveDataGUIentry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataGUIentry

//______________________________________________________________________________
void LiveDataGUIStyleControl::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataGUIStyleControl.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataGUIStyleControl::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataGUIStyleControl::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataGUIStyleControl(void *p) {
      return  p ? new(p) ::LiveDataGUIStyleControl : new ::LiveDataGUIStyleControl;
   }
   static void *newArray_LiveDataGUIStyleControl(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataGUIStyleControl[nElements] : new ::LiveDataGUIStyleControl[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataGUIStyleControl(void *p) {
      delete ((::LiveDataGUIStyleControl*)p);
   }
   static void deleteArray_LiveDataGUIStyleControl(void *p) {
      delete [] ((::LiveDataGUIStyleControl*)p);
   }
   static void destruct_LiveDataGUIStyleControl(void *p) {
      typedef ::LiveDataGUIStyleControl current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataGUIStyleControl

//______________________________________________________________________________
void LiveDataAdjuster::Streamer(TBuffer &R__b)
{
   // Stream an object of class LiveDataAdjuster.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LiveDataAdjuster::Class(),this);
   } else {
      R__b.WriteClassBuffer(LiveDataAdjuster::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LiveDataAdjuster(void *p) {
      return  p ? new(p) ::LiveDataAdjuster : new ::LiveDataAdjuster;
   }
   static void *newArray_LiveDataAdjuster(Long_t nElements, void *p) {
      return p ? new(p) ::LiveDataAdjuster[nElements] : new ::LiveDataAdjuster[nElements];
   }
   // Wrapper around operator delete
   static void delete_LiveDataAdjuster(void *p) {
      delete ((::LiveDataAdjuster*)p);
   }
   static void deleteArray_LiveDataAdjuster(void *p) {
      delete [] ((::LiveDataAdjuster*)p);
   }
   static void destruct_LiveDataAdjuster(void *p) {
      typedef ::LiveDataAdjuster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LiveDataAdjuster

namespace ROOT {
   // Wrappers around operator new
   static void *new_nuclear_data_ob(void *p) {
      return  p ? new(p) ::nuclear_data_ob : new ::nuclear_data_ob;
   }
   static void *newArray_nuclear_data_ob(Long_t nElements, void *p) {
      return p ? new(p) ::nuclear_data_ob[nElements] : new ::nuclear_data_ob[nElements];
   }
   // Wrapper around operator delete
   static void delete_nuclear_data_ob(void *p) {
      delete ((::nuclear_data_ob*)p);
   }
   static void deleteArray_nuclear_data_ob(void *p) {
      delete [] ((::nuclear_data_ob*)p);
   }
   static void destruct_nuclear_data_ob(void *p) {
      typedef ::nuclear_data_ob current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::nuclear_data_ob

namespace ROOT {
   // Wrappers around operator new
   static void *new_cNucleusIterator(void *p) {
      return  p ? new(p) ::cNucleusIterator : new ::cNucleusIterator;
   }
   static void *newArray_cNucleusIterator(Long_t nElements, void *p) {
      return p ? new(p) ::cNucleusIterator[nElements] : new ::cNucleusIterator[nElements];
   }
   // Wrapper around operator delete
   static void delete_cNucleusIterator(void *p) {
      delete ((::cNucleusIterator*)p);
   }
   static void deleteArray_cNucleusIterator(void *p) {
      delete [] ((::cNucleusIterator*)p);
   }
   static void destruct_cNucleusIterator(void *p) {
      typedef ::cNucleusIterator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cNucleusIterator

namespace ROOT {
   // Wrappers around operator new
   static void *new_target(void *p) {
      return  p ? new(p) ::target : new ::target;
   }
   static void *newArray_target(Long_t nElements, void *p) {
      return p ? new(p) ::target[nElements] : new ::target[nElements];
   }
   // Wrapper around operator delete
   static void delete_target(void *p) {
      delete ((::target*)p);
   }
   static void deleteArray_target(void *p) {
      delete [] ((::target*)p);
   }
   static void destruct_target(void *p) {
      typedef ::target current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::target

namespace ROOT {
   // Wrappers around operator new
   static void *new_cNucleus(void *p) {
      return  p ? new(p) ::cNucleus : new ::cNucleus;
   }
   static void *newArray_cNucleus(Long_t nElements, void *p) {
      return p ? new(p) ::cNucleus[nElements] : new ::cNucleus[nElements];
   }
   // Wrapper around operator delete
   static void delete_cNucleus(void *p) {
      delete ((::cNucleus*)p);
   }
   static void deleteArray_cNucleus(void *p) {
      delete [] ((::cNucleus*)p);
   }
   static void destruct_cNucleus(void *p) {
      typedef ::cNucleus current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cNucleus

namespace ROOT {
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary();
   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEintgRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEintgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p);
   static void destruct_vectorlEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<int> >*)
   {
      vector<vector<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<int> >", -2, "vector", 210,
                  typeid(vector<vector<int> >), DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<int> >) );
      instance.SetNew(&new_vectorlEvectorlEintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEintgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<int> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<int> >*)0x0)->GetClass();
      vectorlEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<int> > : new vector<vector<int> >;
   }
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<int> >[nElements] : new vector<vector<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEintgRsPgR(void *p) {
      delete ((vector<vector<int> >*)p);
   }
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p) {
      delete [] ((vector<vector<int> >*)p);
   }
   static void destruct_vectorlEvectorlEintgRsPgR(void *p) {
      typedef vector<vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<int> >

namespace ROOT {
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 210,
                  typeid(vector<vector<double> >), DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<double> >*)0x0)->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete ((vector<vector<double> >*)p);
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] ((vector<vector<double> >*)p);
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 210,
                  typeid(vector<int>), DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 210,
                  typeid(vector<double>), DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETGraphmUgR_Dictionary();
   static void vectorlETGraphmUgR_TClassManip(TClass*);
   static void *new_vectorlETGraphmUgR(void *p = 0);
   static void *newArray_vectorlETGraphmUgR(Long_t size, void *p);
   static void delete_vectorlETGraphmUgR(void *p);
   static void deleteArray_vectorlETGraphmUgR(void *p);
   static void destruct_vectorlETGraphmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGraph*>*)
   {
      vector<TGraph*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGraph*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGraph*>", -2, "vector", 210,
                  typeid(vector<TGraph*>), DefineBehavior(ptr, ptr),
                  &vectorlETGraphmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGraph*>) );
      instance.SetNew(&new_vectorlETGraphmUgR);
      instance.SetNewArray(&newArray_vectorlETGraphmUgR);
      instance.SetDelete(&delete_vectorlETGraphmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGraphmUgR);
      instance.SetDestructor(&destruct_vectorlETGraphmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGraph*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TGraph*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGraphmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGraph*>*)0x0)->GetClass();
      vectorlETGraphmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGraphmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGraphmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TGraph*> : new vector<TGraph*>;
   }
   static void *newArray_vectorlETGraphmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TGraph*>[nElements] : new vector<TGraph*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGraphmUgR(void *p) {
      delete ((vector<TGraph*>*)p);
   }
   static void deleteArray_vectorlETGraphmUgR(void *p) {
      delete [] ((vector<TGraph*>*)p);
   }
   static void destruct_vectorlETGraphmUgR(void *p) {
      typedef vector<TGraph*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGraph*>

namespace ROOT {
   static TClass *vectorlELiveDataGUIentrymUgR_Dictionary();
   static void vectorlELiveDataGUIentrymUgR_TClassManip(TClass*);
   static void *new_vectorlELiveDataGUIentrymUgR(void *p = 0);
   static void *newArray_vectorlELiveDataGUIentrymUgR(Long_t size, void *p);
   static void delete_vectorlELiveDataGUIentrymUgR(void *p);
   static void deleteArray_vectorlELiveDataGUIentrymUgR(void *p);
   static void destruct_vectorlELiveDataGUIentrymUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LiveDataGUIentry*>*)
   {
      vector<LiveDataGUIentry*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LiveDataGUIentry*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LiveDataGUIentry*>", -2, "vector", 210,
                  typeid(vector<LiveDataGUIentry*>), DefineBehavior(ptr, ptr),
                  &vectorlELiveDataGUIentrymUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<LiveDataGUIentry*>) );
      instance.SetNew(&new_vectorlELiveDataGUIentrymUgR);
      instance.SetNewArray(&newArray_vectorlELiveDataGUIentrymUgR);
      instance.SetDelete(&delete_vectorlELiveDataGUIentrymUgR);
      instance.SetDeleteArray(&deleteArray_vectorlELiveDataGUIentrymUgR);
      instance.SetDestructor(&destruct_vectorlELiveDataGUIentrymUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LiveDataGUIentry*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<LiveDataGUIentry*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELiveDataGUIentrymUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LiveDataGUIentry*>*)0x0)->GetClass();
      vectorlELiveDataGUIentrymUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELiveDataGUIentrymUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELiveDataGUIentrymUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<LiveDataGUIentry*> : new vector<LiveDataGUIentry*>;
   }
   static void *newArray_vectorlELiveDataGUIentrymUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<LiveDataGUIentry*>[nElements] : new vector<LiveDataGUIentry*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELiveDataGUIentrymUgR(void *p) {
      delete ((vector<LiveDataGUIentry*>*)p);
   }
   static void deleteArray_vectorlELiveDataGUIentrymUgR(void *p) {
      delete [] ((vector<LiveDataGUIentry*>*)p);
   }
   static void destruct_vectorlELiveDataGUIentrymUgR(void *p) {
      typedef vector<LiveDataGUIentry*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LiveDataGUIentry*>

namespace {
  void TriggerDictionaryInitialization_DictOutput_Impl() {
    static const char* headers[] = {
"include/james_LeeNucleusExtend.h",
"include/james_nuclear_data_gui.h",
"include/james_nuclear_data_ob.h",
"include/james_fission.h",
"include/james_root_maths.h",
"include/james_legendre.h",
"include/james_target.h",
"include/james_physics.h",
"include/james_physhist_format.h",
0
    };
    static const char* includePaths[] = {
"/home/jsmallcombe/Dropbox/codes/JPhysics/include",
"/opt/root_v6.04.12/include/root",
"/home/jsmallcombe/Dropbox/codes/JPhysics/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_LeeNucleusExtend.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_LeeNucleusExtend.h")))  cNucleusInh;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_LeeNucleusExtend.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_LeeNucleusExtend.h")))  NucDatumSpecifier;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_legendre.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_legendre.h")))  legendre_polynomials;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_legendre.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_legendre.h")))  spherical_harmonic;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_legendre.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_legendre.h")))  gamma_dist;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataSlicer;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataAdder;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataAdderLevelSelect;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  PadScanData;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataGUIentry;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataGUIStyleControl;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_gui.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  LiveDataAdjuster;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_ob.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  nuclear_data_ob;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_nuclear_data_ob.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_nuclear_data_gui.h")))  cNucleusIterator;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_target.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_fission.h")))  target;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/LeeNucleus.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_LeeNucleusExtend.h")))  cNucleus;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/james_LeeNucleusExtend.h"
#include "include/james_nuclear_data_gui.h"
#include "include/james_nuclear_data_ob.h"
#include "include/james_fission.h"
#include "include/james_root_maths.h"
#include "include/james_legendre.h"
#include "include/james_target.h"
#include "include/james_physics.h"
#include "include/james_physhist_format.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"", payloadCode, "@",
"Acos", payloadCode, "@",
"AddElectronGammaLabels", payloadCode, "@",
"AddElectronLabel", payloadCode, "@",
"Asin", payloadCode, "@",
"Atan", payloadCode, "@",
"DetectorCoMAngles", payloadCode, "@",
"DetectorCoMAnglesElastic", payloadCode, "@",
"K_bind_aprox_keV", payloadCode, "@",
"LiveDataAdder", payloadCode, "@",
"LiveDataAdder::fgIsA", payloadCode, "@",
"LiveDataAdderLevelSelect", payloadCode, "@",
"LiveDataAdderLevelSelect::fgIsA", payloadCode, "@",
"LiveDataAdjuster", payloadCode, "@",
"LiveDataAdjuster::fgIsA", payloadCode, "@",
"LiveDataGUIStyleControl", payloadCode, "@",
"LiveDataGUIStyleControl::fgIsA", payloadCode, "@",
"LiveDataGUIentry", payloadCode, "@",
"LiveDataGUIentry::fgIsA", payloadCode, "@",
"LiveDataSlicer", payloadCode, "@",
"LiveDataSlicer::fgIsA", payloadCode, "@",
"NucDatumSpecifier", payloadCode, "@",
"PadScanData", payloadCode, "@",
"PadScanData::CurrentDraw", payloadCode, "@",
"PadScanData::numbertodisplay", payloadCode, "@",
"TGComboBoxMarkerSelect", payloadCode, "@",
"W_182_straight", payloadCode, "@",
"W_182_twisted", payloadCode, "@",
"W_184_straight", payloadCode, "@",
"W_184_twisted", payloadCode, "@",
"W_186_straight", payloadCode, "@",
"W_186_twisted", payloadCode, "@",
"Z_90_straight", payloadCode, "@",
"alight_to_Z", payloadCode, "@",
"angledifference", payloadCode, "@",
"angledifference_signed", payloadCode, "@",
"beta_fermi_fn_aprox", payloadCode, "@",
"cNucleus", payloadCode, "@",
"cNucleusInh", payloadCode, "@",
"cNucleusIterator", payloadCode, "@",
"classical_barrier", payloadCode, "@",
"classical_radius", payloadCode, "@",
"clebsch_print", payloadCode, "@",
"clebschgordancoefficients", payloadCode, "@",
"cos2", payloadCode, "@",
"deg2rad", payloadCode, "@",
"eloss_mass_grapher", payloadCode, "@",
"fission_compound_split", payloadCode, "@",
"fission_compound_unit", payloadCode, "@",
"gamma_dist", payloadCode, "@",
"get_KE", payloadCode, "@",
"get_beta", payloadCode, "@",
"get_beta_KE", payloadCode, "@",
"get_beta_mom", payloadCode, "@",
"get_beta_vec", payloadCode, "@",
"get_com_KE", payloadCode, "@",
"get_com_KE_MeVbeam", payloadCode, "@",
"get_com_beta", payloadCode, "@",
"get_com_beta_vec", payloadCode, "@",
"get_gamma", payloadCode, "@",
"get_gamma_KE", payloadCode, "@",
"get_gamma_mom", payloadCode, "@",
"get_relE_KE", payloadCode, "@",
"get_relE_mom", payloadCode, "@",
"get_rel_mom", payloadCode, "@",
"giveme_areal", payloadCode, "@",
"giveme_um", payloadCode, "@",
"happy_phi", payloadCode, "@",
"happy_ruth_theta", payloadCode, "@",
"j_int_fac", payloadCode, "@",
"jam_phys_511", payloadCode, "@",
"jam_phys_amu", payloadCode, "@",
"jam_phys_amu_kg", payloadCode, "@",
"jam_phys_charge", payloadCode, "@",
"jam_phys_e4pieps", payloadCode, "@",
"jam_phys_np_mass", payloadCode, "@",
"jam_phys_speed_c", payloadCode, "@",
"jam_phys_speed_c_mm_ns", payloadCode, "@",
"jhic", payloadCode, "@",
"kin_labels", payloadCode, "@",
"kinetic_CM_to_lab_angle", payloadCode, "@",
"kinetic_CM_to_lab_angle_elastic", payloadCode, "@",
"kinetic_lab_calcs_E", payloadCode, "@",
"kinetic_lab_calcs_P", payloadCode, "@",
"kinetic_lab_calcs_elastic_E", payloadCode, "@",
"kinetic_lab_calcs_elastic_P", payloadCode, "@",
"kinetic_lab_calcs_readout", payloadCode, "@",
"lab_boost_CMP_query", payloadCode, "@",
"legendre_polynomials", payloadCode, "@",
"make_lorentzvec", payloadCode, "@",
"mass_convert", payloadCode, "@",
"mass_split_calc", payloadCode, "@",
"mom_conserve_split", payloadCode, "@",
"mom_conserve_unit", payloadCode, "@",
"momentum_beam_P_CoM", payloadCode, "@",
"momentum_energysplit_CoM", payloadCode, "@",
"neck_TKE_manea", payloadCode, "@",
"nuclear_data_ob", payloadCode, "@",
"nuclear_data_ob::LeeFile", payloadCode, "@",
"nuclear_data_ob::LeeTree", payloadCode, "@",
"nuclear_data_ob::ScanTransEnergy", payloadCode, "@",
"nuclear_data_ob::ScanTransString", payloadCode, "@",
"nuclear_data_ob::data_set", payloadCode, "@",
"nuclear_data_ob::elem_sym_list", payloadCode, "@",
"nuclear_data_ob::level_width", payloadCode, "@",
"nuclear_data_ob::live_data", payloadCode, "@",
"nuclear_data_ob::live_data_color", payloadCode, "@",
"nuclear_data_ob::live_data_lower_error", payloadCode, "@",
"nuclear_data_ob::live_data_marker", payloadCode, "@",
"nuclear_data_ob::live_data_names", payloadCode, "@",
"nuclear_data_ob::live_data_type", payloadCode, "@",
"nuclear_data_ob::live_data_upper_error", payloadCode, "@",
"nuclear_data_ob::livedatapick", payloadCode, "@",
"pi", payloadCode, "@",
"rad2deg", payloadCode, "@",
"reverseal_beta_calc", payloadCode, "@",
"reverseal_beta_calc_KE", payloadCode, "@",
"reverseal_mom_calc", payloadCode, "@",
"reverseal_mom_calc_KE", payloadCode, "@",
"rutherford_crosssection", payloadCode, "@",
"rutherford_crosssection_lab", payloadCode, "@",
"safe_coulex_angle", payloadCode, "@",
"safe_coulex_beam", payloadCode, "@",
"safe_r", payloadCode, "@",
"set_global_compound", payloadCode, "@",
"sin2", payloadCode, "@",
"spherical_harmonic", payloadCode, "@",
"tan2", payloadCode, "@",
"target", payloadCode, "@",
"target_effective", payloadCode, "@",
"unnorm_beta_dist_TKE", payloadCode, "@",
"viola_TKE", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DictOutput",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DictOutput_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DictOutput_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DictOutput() {
  TriggerDictionaryInitialization_DictOutput_Impl();
}