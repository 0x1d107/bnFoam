#ifndef PH_F 
#define PH_F(X) X
#define PH_FS(X) #X
#endif
Info<< "Reading field "<<PH_FS(U)<<"\n" << endl;
volVectorField PH_F(U)
(
    IOobject
    (
        PH_FS(U),
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField PH_F(rho)
(
    IOobject
    (
        PH_FS(rho),
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    thermo.rho()
);

volVectorField PH_F(rhoU)
(
    IOobject
    (
        PH_FS(rhoU),
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    PH_F(rho)*PH_F(U)
);

volScalarField PH_F(rhoE)
(
    IOobject
    (
        PH_FS(rhoE),
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    PH_F(rho)*(e + 0.5*magSqr(PH_F(U)))
);

surfaceScalarField PH_F(phi) (PH_FS(phi), fvc::flux(PH_F(rhoU)));

