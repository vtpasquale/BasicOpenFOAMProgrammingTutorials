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

    Exercise 2 (Page 170)
    Write a program that reads an OpenFOAM® mesh and checks that for each element
    the sum of the surface vectors is zero.
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

	// These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    #include "createTime.H"
    #include "createMesh.H"

	// 
	Info << "Read the mesh and check that for each element the sum of the surface vectors is zero." << nl << endl;


    // Cheat sheet
    // https://jibranhaider.com/blog/mesh-information-in-openfoam/
 
    // Cell to face list
    const Foam::cellList& cells = mesh.cells();

    // Face area normal vectors
    const Foam::surfaceVectorField& faceAreaNormalVectors = mesh.Sf();
    
    // Check indexing
    /*---------------------------------------------------------------------------*\
    forAll(cells,i)
    {
        Info << "I = " << I << "  cells[i]  = " << cells[i];
        forAll(cells[i],j)
        {
            Info << " " << cells[i][j];
        }
        Info << endl; 
    }
    \*---------------------------------------------------------------------------*/

    const vector zeroVector(0.0,0.0,0.0);
    vector sumVector = zeroVector;

    Info << "Zero vector = "<< zeroVector << endl;
    forAll(cells,i)
    {
        sumVector = zeroVector;
        forAll(cells[i],j)
        {
            sumVector = sumVector + faceAreaNormalVectors[cells[i][j]];
        }
        Info << "Cell " << i << " sum(sF) = " << sumVector << endl; 
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
