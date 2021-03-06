{  
  // Create point interpolation
  volPointInterpolation pointInterpolation(mesh);


  // Calculate mesh points displacement
  pointVectorField pointU = pointInterpolation.interpolate(U);

  //  const vectorField& pointUI = pointU.internalField();
  vectorField pointUI = pointU.internalField();
  

  // Move mesh
  //vectorField newPoints = mesh.allPoints();
  vectorField newPoints = mesh.points();  
  
  forAll (pointUI, pointI)
    {
      newPoints[pointI] += pointUI[pointI];
    }

# include "correctGlobalFaceZoneMesh.H"
 
  twoDPointCorrector twoDCorrector(mesh);
  twoDCorrector.correctPoints(newPoints);  
  
  mesh.movePoints(newPoints);
  //  pMesh.movePoints(newPoints);
  mesh.V00();
  mesh.moving(false);
}
