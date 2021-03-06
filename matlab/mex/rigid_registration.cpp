#include "mex.h"
#include <meshmonk.hpp>
#include "mystream.cpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    
    //# Check input
    //## Number of input arguments
    if(nlhs != 0) {
    mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs",
                      "Zero LHS output required.");
    }
    //## Number of output arguments
    if(nrhs != 15) {
    mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs",
                      "15 inputs required.");
    }
    
    //# Get Inputs
    //## Floating Features
    float *floatingFeatures = reinterpret_cast<float *>(mxGetData(prhs[0]));
    mwSize numFloatingElements = mxGetM(prhs[0]);
    //## Target Features
    float *targetFeatures = reinterpret_cast<float *>(mxGetData(prhs[1]));
    mwSize numTargetElements = mxGetM(prhs[1]);
    //## Floating Faces
    int *floatingFaces = reinterpret_cast<int *>(mxGetData(prhs[2]));
    mwSize numFloatingFaces = mxGetM(prhs[2]);
    //## Target Faces
    int *targetFaces = reinterpret_cast<int *>(mxGetData(prhs[3]));
    mwSize numTargetFaces = mxGetM(prhs[3]);
    //## FLoating Flags
    float *floatingFlags = reinterpret_cast<float *>(mxGetData(prhs[4]));
    //## Target Flags
    float *targetFlags = reinterpret_cast<float *>(mxGetData(prhs[5]));
    //## Transformation Matrix
    float *transformationMatrix = reinterpret_cast<float *>(mxGetData(prhs[6]));
    //## Parameters
    //### Total number of iterations
    mwSize numIterations = static_cast<mwSize>(mxGetScalar(prhs[7]));
    //### Use symmetric correspondences
    bool correspondencesSymmetric = static_cast<bool>(mxGetScalar(prhs[8]));
    //### Number of neighbours to use to compute corresponding points
    mwSize correspondencesNumNeighbours = static_cast<mwSize>(mxGetScalar(prhs[9]));
    //### Flag threshold to mark corresponding flag as 0.0 or 1.0
    float correspondencesFlagThreshold = static_cast<float>(mxGetScalar(prhs[10]));
    //### Equalize the push and pull forces (when using symmetric correspondences)
    bool correspondencesEqualizePushPull = static_cast<bool>(mxGetScalar(prhs[11]));
    //### Inlier kappa
    float inlierKappa = static_cast<float>(mxGetScalar(prhs[12]));
    //### Inlier Orientation
    float inlierUseOrientation = static_cast<float>(mxGetScalar(prhs[13]));
    //### Allow Scaling
    bool useScaling = static_cast<bool>(mxGetScalar(prhs[14]));
    
    
    //# Execute c++ function
    meshmonk::rigid_registration_mex(floatingFeatures, targetFeatures,
                                numFloatingElements, numTargetElements,
                                floatingFaces, targetFaces,
                                numFloatingFaces, numTargetFaces,
                                floatingFlags, targetFlags,
                                transformationMatrix,
                                numIterations,
                                correspondencesSymmetric, correspondencesNumNeighbours,
                                correspondencesFlagThreshold, correspondencesEqualizePushPull,
                                inlierKappa, inlierUseOrientation,
                                useScaling);
    
//     //# Set Output
//     int numCols = 6;
//     plhs[0] = mxCreateNumericMatrix(numFloatingElements, numCols, mxSINGLE_CLASS, mxREAL); // output: double matrix
//     auto output = mxGetPr(plhs[0]);
//     //## Copy result form c++ function into the output
//     for (unsigned i = 0 ; i < numFloatingElements * numCols ; i++){
//         output[i] = floatingFeatures[i];
//     }
  
}
