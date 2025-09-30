#pragma once 
#include <fvCFD.H>
#include "IOobject.H"
#include "psiThermo.H"
#include "volFieldsFwd.H"

struct phaseFields{
	autoPtr<psiThermo> pThermo;
	volVectorField U;
	volScalarField rho;
	volVectorField rhoU;
	volScalarField rhoE;
	surfaceScalarField phi;
	void init(const Foam::word& prefix,const Foam::fvMesh &mesh,const Foam::word &timeName){
	pThermo = psiThermo::New(mesh);
	volScalarField &e = pThermo().he();
#define FIELD(type,name,...) name = type(IOobject(prefix+#name,timeName,mesh,__VA_ARGS__),mesh)
	FIELD(volVectorField,U,IOobject::MUST_READ,IOobject::AUTO_WRITE);
	FIELD(volScalarField,rho,IOobject::MUST_READ,IOobject::AUTO_WRITE);
	rhoU= volVectorField
	(
		IOobject
		(
			prefix+"rhoU",
			timeName,
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		rho*U
	);
	rhoE = volScalarField 
	(
		IOobject
		(
			prefix+"rhoE",
			timeName,
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		rho*(e + 0.5*magSqr(U))
	);

#undef FIELD
	}	
};
