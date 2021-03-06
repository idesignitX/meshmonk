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
    if(nrhs != 9) {
    mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs",
                      "9 inputs required.");
    }
    
    //# Get Inputs
    //## Floating Features
    float *floatingFeatures = reinterpret_cast<float *>(mxGetData(prhs[0]));
    mwSize numFloatingElements = mxGetM(prhs[0]);
    //## Corresponding Features
    float *correspondingFeatures = reinterpret_cast<float *>(mxGetData(prhs[1]));
    //## Floating Faces
    int *floatingFaces = reinterpret_cast<int *>(mxGetData(prhs[2]));
    mwSize numFloatingFaces = mxGetM(prhs[2]);
    //## FLoating Flags
    float *floatingFlags = reinterpret_cast<float *>(mxGetData(prhs[3]));
    //## Inlier Weights
    float *inlierWeights = reinterpret_cast<float *>(mxGetData(prhs[4]));
    //## Parameters
    //### Number of neighbours used for smoothing the deformation field
    mwSize transformNumNeighbours = static_cast<mwSize>(mxGetScalar(prhs[5]));
    //### Sigma of gaussian used in visco-elastic smoothing of deformation field
    float transformSigma = static_cast<float>(mxGetScalar(prhs[6]));
    //### Number of viscous smoothing iterations
    mwSize transformNumViscousIterations = static_cast<mwSize>(mxGetScalar(prhs[7]));
    //### Number of elastic smoothing iterations
    mwSize transformNumElasticIterations = static_cast<mwSize>(mxGetScalar(prhs[8]));
    
    //# Execute c++ function    
    meshmonk::compute_nonrigid_transformation_mex(floatingFeatures, correspondingFeatures,
                                                numFloatingElements,
                                                floatingFaces, numFloatingFaces,
                                                floatingFlags, inlierWeights,
                                                transformNumNeighbours, transformSigma,
                                                transformNumViscousIterations, transformNumElasticIterations);
    
//     //# Set Output
//     plhs[0] = mxCreateNumericMatrix(numFloatingElements, 6, mxSINGLE_CLASS, mxREAL); // output: double matrix
//     auto output = mxGetPr(plhs[0]);
//     //## Copy result form c++ function into the output
//     for (unsigned i = 0 ; i < numFloatingElements * 6 ; i++){
//         output[i] = floatingFeatures[i];
//     }
  
}