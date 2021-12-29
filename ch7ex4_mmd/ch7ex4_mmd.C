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

#include "fvCFD.H"

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

	// These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    #include "createTime.H"
    #include "createMesh.H"

	// 
	Info << "This is my updated, again, program" << nl << endl;

    // Face Data
    labelUList faceOwner = mesh.owner();
    labelUList faceNeighbour = mesh.neighbour();
    surfaceVectorField faceCenter = mesh.Cf();

    Info << "These sizes should be equal: " << faceOwner.size() << ", " 
                                            << faceNeighbour.size() << ", "
                                            << faceCenter.size() << nl << endl;

    forAll(faceCenter, faceI)
        if (faceI%40 == 0)
            Info << "Internal Face " << faceI 
            << ", Owner: " << faceOwner[faceI]
            << ", Neighbour: " << faceNeighbour[faceI]
            << ", Center: " << faceCenter[faceI] << endl;
    Info << endl; // spacer

    // Element Data
    const scalar my13 = 1./3.;
    Info << "Check 1/3 = " << my13 << endl;
    DimensionedField< scalar, volMesh > cellVolume = mesh.V();
    DimensionedField< scalar, volMesh > cubeRootVolume = Foam::pow(cellVolume,my13);
    volVectorField cellCenter = mesh.C();

    forAll(cellVolume, cellI)
        if (cellI%40 == 0)
            Info << "Cell " << cellI
            << ", Center = " << cellCenter[cellI]
            << ", Volume = " << cellVolume[cellI]
            << " , CubeRootVolume = " << cubeRootVolume[cellI] << endl;


    // Loop over all boundary faces and write for each face the owner (parentCell)
    // and centroid.
    const fvBoundaryMesh & boundaryMesh = mesh.boundary();
    Info << nl << "boundaryMesh.size() = " << boundaryMesh.size() << nl << endl;
    forAll(boundaryMesh,patchI)
        Info << "Patch " << patchI 
        << ", Name " << boundaryMesh[patchI].name()
        << ", Start " << boundaryMesh[patchI].start() << endl;


    


    


    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
