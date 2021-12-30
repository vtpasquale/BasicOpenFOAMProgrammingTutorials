/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
    The Finite Volume Method in Computational Fluid Dynamics
    F. Moukalled, L. Mangani, M. Darwish

    Chpater 7 Exercise 3 (Page 206)
    Use blockMesh to setup a uniform mesh similar to the one in Fig. 7.12 for L = 1. In
    OpenFOAM® and then in uFVM do the following:

    (a) Write a program to read the mesh and loop over all boundary patches. Then
    for each patch print the centroid and normal vector of its faces.

    (b) Modify the program to define a volumeScalarField T. Set the values for T at
    element centroids and at the boundaries to 10x2y2, where x and y are the
    coordinates of the element centroids and for the case of the boundary the
    centroids of the boundary faces.

    (c) Write a program to compute the gradient of T and compare its value with the
    analytical solution.

\*---------------------------------------------------------------------------*/


#include "fvCFD.H"

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

	// These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    #include "createTime.H"
    #include "createMesh.H"

    /*---------------------------------------------------------------------------*\
    (c) Write a program to compute the gradient of T and compare its value with the
    analytical solution.
    \*---------------------------------------------------------------------------*/
    Info<< "Reading field T\n" << endl;
	volScalarField T
	(
		IOobject
		(
		    "T",
		    runTime.timeName(),
		    mesh,
		    IOobject::MUST_READ,
		    IOobject::AUTO_WRITE
		),
		mesh
	);

    // Field checks
    Info << "volScalarField T = " << endl;
    Info << T << nl << endl;

    // Update runtime
    Info << runTime.time().value() << endl;
    runTime.loop();
    Info << runTime.time().value() << endl;
    Info << nl << endl;

    // compute the gauss gradient of T
	volVectorField gdT
	(
		IOobject
		(
		    "gdT",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
        fvc::grad(T)
	);
    Info << gdT << endl;

    // Analytic gradient placeholder
	volVectorField adT
	(
		IOobject
		(
		    "adT",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
        fvc::grad(T)
	);

    // compute analytic gradient
    const volVectorField& C = mesh.C(); // Cell center coordinates
    forAll(adT,i){
        adT[i][0]  =  20.*C[i][0] * C[i][1] * C[i][1];
        adT[i][1]  =  20.*C[i][0] * C[i][0] * C[i][1];
    }
    Info << adT << endl;

    // Error 
	volVectorField edT
	(
		IOobject
		(
		    "edT",
		    runTime.timeName(),
		    mesh,
		    IOobject::NO_READ,
		    IOobject::AUTO_WRITE
		),
        adT - gdT
	);
    Info << edT << endl;

    runTime.writeNow();
    return 0;
}


// ************************************************************************* //
