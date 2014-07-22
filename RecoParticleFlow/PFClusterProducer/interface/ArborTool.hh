#ifndef ARBORTOOL_H_
#define ARBORTOOL_H_

#include "TVector3.h"
#include "TMatrixF.h"
#include <iostream>
#include <vector>
#include <string>

namespace arbor{

typedef std::vector< std::vector<int> > branchcoll;
typedef std::vector<int> branch;
typedef std::vector< std::pair<int, int> > linkcoll;


TMatrixF MatrixSummarize( TMatrixF inputMatrix );		//ArborCoreNeed

std::vector<int>SortMeasure( std::vector<float> Measure, int ControlOrderFlag );	//ArborCoreNeed

branchcoll ArborBranchMerge(branchcoll inputbranches, TMatrixF inputMatrix);		//ArborCoreNeed

}
#endif //
