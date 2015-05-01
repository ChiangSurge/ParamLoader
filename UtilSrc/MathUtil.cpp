#include <cmath>
#include <set>
#include <map>
#include <limits>
#include "Utils.h"
using namespace std;

vector<double> MathUtil::stored_random_number_array;

typedef vector<RNScalar> ScalarArray;
RNScalar MathUtil::
Sum(const vector<RNScalar>& array)
{
    RNScalar sum = 0;
    for (int i=0; i<int(array.size()); i++)
    {
        sum += array[i];
    }
    return sum;
}

int MathUtil::
Sum(const vector<int>& array)
{
    int sum = 0;
    for (int i=0; i<int(array.size()); i++)
    {
        sum += array[i];
    }
    return sum;
}

void MathUtil::
DivideBySum(vector<double>& array)
{
	double sum = Sum(array);
	if (sum == 0.0) return;
	for (int i=0; i<int(array.size()); i++) {
		array[i] /= sum;
	}
}

RNScalar MathUtil::
Average(const vector<RNScalar>& array)
{
    if (array.size() == 0) return 0.0;
    return Sum(array)/int(array.size());
}

const ScalarArray MathUtil::
Average(const vector<ScalarArray>& array, int nDims)
{
    ScalarArray ans(nDims, 0);
    vector<ScalarArray> data(nDims);
    for (int i=0; i<(int)array.size(); i++) {
        assert(array[i].size() == nDims);
        for (int j=0; j<nDims; j++) {
            data[j].push_back(array[i][j]);
        }
    }
    for (int i=0; i<nDims; i++) {
        ans[i] = Average(data[i]);
    }
    return ans;
}

RNScalar MathUtil::
Maximum(const vector<RNScalar>& array, int* p)
{
    RNScalar max = -FLT_MAX;
    for (int i=0; i<int(array.size()); i++)
    {
        if (array[i] > max)
        {
            max = array[i];
            if (p) *p = i;
        }
    }
    return max;
}

int MathUtil::
Maximum(const vector<int>& array, int* p)
{
    int max = 0;
    int maxIdx = -1;
    for (int i=0; i<(int)array.size(); i++) {
        if (array[i] > max || maxIdx == -1) {
            max = array[i];
            maxIdx = i;
        }
    }
    if (p) *p = maxIdx;
    return max;
}

const vector<int> MathUtil::
KthMaximum(const vector<RNScalar>& array, int k)
{
    vector<int> maxIndices;
    vector<bool> visitedFlags(array.size(), false);
    for (int i=0; i<k; i++) {
        int maxIdx = -1;
        double maxNum = 0;
        for (int j=0; j<(int)array.size(); j++) {
            if (visitedFlags[j]) continue;
            if (array[j] > maxNum || maxIdx == -1) {
                maxNum = array[j];
                maxIdx = j;
            }
        }
        if (maxIdx == -1) return maxIndices;
        maxIndices.push_back(maxIdx);
        visitedFlags[maxIdx] = true;
    }
    return maxIndices;
}

const vector<int> MathUtil::
KthMinimum(const vector<RNScalar>& array, int k)
{
    vector<int> minIndices;
    vector<bool> visitedFlags(array.size(), false);
    for (int i=0; i<k; i++) {
        int minIdx = -1;
        double minNum = 0;
        for (int j=0; j<(int)array.size(); j++) {
            if (visitedFlags[j]) continue;
            if (array[j] < minNum || minIdx == -1) {
                minNum = array[j];
                minIdx = j;
            }
        }
        if (minIdx == -1) return minIndices;
        minIndices.push_back(minIdx);
        visitedFlags[minIdx] = true;
    }
    return minIndices;
}


RNScalar MathUtil::
Minimum(const vector<RNScalar>& array, int* p)
{
    RNScalar min = FLT_MAX;
    for (int i=0; i<int(array.size()); i++)
    {
        if (array[i] < min)
        {
            min = array[i];
            if (p) *p = i;
        }
    }
    return min;
}

int MathUtil::
Minimum(const vector<int>& array, int* p)
{
    int min = 1000000000;
    for (int i=0; i<int(array.size()); i++)
    {
        if (array[i] < min)
        {
            min = array[i];
            if (p) *p = i;
        }
    }
    return min;
}

RNScalar MathUtil::
StandardDeviation(const vector<RNScalar>& array)
{
    if (array.size() == 0) return 0.0;
    RNScalar avg = Average(array);
    RNScalar sum = 0;
    for (int i=0; i<int(array.size()); i++)
    {
        RNScalar diff = array[i] - avg;
        sum += diff * diff;
    }
    return sqrt(sum / int(array.size()));
}

const ScalarArray MathUtil::
StandardDeviation(const vector<ScalarArray>& array, int nDims)
{
    ScalarArray ans(nDims, 0);
    vector<ScalarArray> data(nDims);
    for (int i=0; i<(int)array.size(); i++) {
        assert(array[i].size() == nDims);
        for (int j=0; j<nDims; j++) {
            data[j].push_back(array[i][j]);
        }
    }
    for (int i=0; i<nDims; i++) {
        ans[i] = StandardDeviation(data[i]);
    }
    return ans;
}

RNScalar MathUtil::
Sum(const vector<RNScalar>& array, const vector<RNScalar>& weights)
{
    RNScalar sum = 0;
    for (int i=0; i<int(array.size()); i++)
    {
        sum += array[i]*weights[i];
    }
    return sum;
}

RNScalar MathUtil::
Average(const vector<RNScalar>& array, const vector<RNScalar>& weights)
{
    RNScalar sum = Sum(array, weights);
    RNScalar sum_w = Sum(weights);
    if (sum_w != 0)
    {
        sum /= sum_w;
    }
    return sum;
}

RNScalar MathUtil::
StandardDeviation(const vector<RNScalar>& array, const vector<RNScalar>& weights)
{
    RNScalar avg = Average(array, weights);
    vector<RNScalar> diffs;
    for (int i=0; i<int(array.size()); i++)
    {
        RNScalar diff = array[i] - avg;
        diffs.push_back(diff*diff);
    }
    return sqrt(Average(diffs, weights));
}

void MathUtil::
BubbleSort(vector<RNScalar>& values)
{
	vector<int> ranking;
	BubbleSort(values, ranking);
	vector<RNScalar> sorted_array;
	for (int i=0; i<int(ranking.size()); i++) {
		sorted_array.push_back(values[ranking[i]]);
	}
	values = sorted_array;
}

// sort to ascending order
void MathUtil::
BubbleSort(const vector<RNScalar>& values,
		   vector<int>& ranked_index)
{
    int n = values.size();
    ranked_index.clear();
    for (int i=0; i<n; i++)
    {
        ranked_index.push_back(i);
    }
    
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-1-i; j++)
        {
            if (values[ranked_index[j]] > values[ranked_index[j+1]])
            {
                // swap j and j+1
                int temp = ranked_index[j+1];
                ranked_index[j+1] = ranked_index[j];
                ranked_index[j] = temp;
            }
        }
    }
}

void MathUtil::
BubbleSort(vector<int>& values)
{
	vector<int> ranking;
	BubbleSort(values, ranking);
	vector<int> sorted_array;
	for (int i=0; i<int(ranking.size()); i++) {
		sorted_array.push_back(values[ranking[i]]);
	}
	values = sorted_array;
}

void MathUtil::
BubbleSort(const vector<int>& values,
		   vector<int>& ranked_index)
{
    int n = values.size();
    ranked_index.clear();
    for (int i=0; i<n; i++)
    {
        ranked_index.push_back(i);
    }
    
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-1-i; j++)
        {
            if (values[ranked_index[j]] > values[ranked_index[j+1]])
            {
                // swap j and j+1
                int temp = ranked_index[j+1];
                ranked_index[j+1] = ranked_index[j];
                ranked_index[j] = temp;
            }
        }
    }
}

bool MathUtil::
Contains(const std::vector<R3MySceneNode*>& array1,
		 const std::vector<R3MySceneNode*>& array2)
{
	for (int i=0; i<int(array2.size()); i++) {
		bool suc_flag = false;
		for (int j=0; j<int(array1.size()); j++) {
			if (array1[j] == array2[i]) {
				suc_flag = true;
				break;
			}
		}
		if (!suc_flag) return false;
	}
	return true;
}

vector<R3MySceneNode*> MathUtil::
Intersect(const vector<R3MySceneNode*>& array1,
		  const vector<R3MySceneNode*>& array2)
{
	set<R3MySceneNode*> set_array2;
	for (int i=0; i<int(array2.size()); i++) {
		set_array2.insert(array2[i]);
	}
	vector<R3MySceneNode*> intersection;
	for (int i=0; i<int(array1.size()); i++) {
		if (set_array2.find(array1[i]) != set_array2.end()) {
			intersection.push_back(array1[i]);
		}
	}
	return intersection;
}


const vector<int>  MathUtil::
Intersect(const vector<int>& array1, const vector<int>& array2)
{
    set<int> setArray2;
    for (int i=0; i<(int)array2.size(); i++) {
        setArray2.insert(array2[i]);
    }
    vector<int> intersection;
    for (int i=0; i<(int)array1.size(); i++) {
        if (setArray2.find(array1[i]) != setArray2.end())
            intersection.push_back(array1[i]);
    }
    return intersection;
}

bool MathUtil::
IsSubSetOfSortedArray(const vector<int>& subset_array,
					  const vector<int>& full_array)
{
	assert(IsSemiAscendinglySorted(subset_array));
	assert(IsSemiAscendinglySorted(full_array));
	int p_in_full_array = 0;
	int p_in_subset_array = 0;
	while (p_in_full_array < int(full_array.size()) &&
		   p_in_subset_array < int(subset_array.size())) {
		if (subset_array[p_in_subset_array] == full_array[p_in_full_array]) {
			p_in_full_array ++;
			p_in_subset_array ++;
		}
		else {
			p_in_full_array ++;
		}
	}
	if (p_in_subset_array == int(subset_array.size())) return true;
	else return false;
}

bool MathUtil::
IsIdenticalToSortedArray(const vector<int>& array1,
						 const vector<int>& array2)
{
	if (array1.size() != array2.size()) return false;
	assert(IsSemiAscendinglySorted(array1));
	assert(IsSemiAscendinglySorted(array2));
	for (int i=0; i<int(array1.size()); i++) {
		if (array1[i] != array2[i]) return false;
	}
	return true;
}

bool MathUtil::
IsIdenticalToArray(const vector<int>& array1, const vector<int>& array2)
{
    if (array1.size() != array2.size()) return false;
    for (int i=0; i<(int)array1.size(); i++) {
        if (array1[i] != array2[i]) return false;
    }
    return true;
}

bool MathUtil::
IsAscendinglySorted(const vector<int>& array)
{
	// array[i] < array[i+1] should be always true
	for (int i=0; i<int(array.size())-1; i++) {
		if (array[i] >= array[i+1]) return false;
	}
	return true;
}

bool MathUtil::
IsSemiAscendinglySorted(const vector<int>& array)
{
	// array[i] < array[i+1] should be always true
	for (int i=0; i<int(array.size())-1; i++) {
		if (array[i] > array[i+1]) return false;
	}
	return true;
}

int MathUtil::
RandomInt(int range)
{
    int rand_int = rand()%range;
    return rand_int;
}

void MathUtil::
InitializeStoredRandomNumbers(int numNumbers)
{
    stored_random_number_array.clear();
    stored_random_number_array.resize(numNumbers, 0);
    for (int i=0; i<numNumbers; i++) {
        stored_random_number_array[i] = RandomNumber(1.0);
    }
}

// we precompute some random numbers from [0, 1.0],
// we fetch them when needed
double MathUtil::
RandomNumberFromStored(double range)
{
    static bool isInitialized = false;
    static int counter = 0;
    static const int numNumbers = 4096;
    if (!isInitialized) {
        InitializeStoredRandomNumbers(numNumbers);
        counter = 0;
        isInitialized = true;
    }
    counter = (counter + 1) % numNumbers;
    return stored_random_number_array[counter]*range;
}


double MathUtil::
RandomNumber(double range)
{
    int int_range = 4096;
    int rand_num = RandomInt(int_range);
    return rand_num*range/int_range;
}

int MathUtil::
RandomItemIndex(const vector<double>& probs)
{
	// linear time solution
	vector<double> norm_probs = probs;
	double sum = Sum(probs);
	if (sum != 0){
		for (int i=0; i<int(norm_probs.size()); i++) {
			norm_probs[i] /= sum;
		}
	}
	double rand = RandomNumber(1.0);
	double sum_so_far = 0;
	for (int i=0; i<int(norm_probs.size()); i++) {
		sum_so_far += norm_probs[i];
		if (sum_so_far > rand) {
			return i;
		}
	}
//	assert(false);
	return int(norm_probs.size())-1;
}

double MathUtil::
RandomFromNormalDistribution(double mean, double sigma)
{
    double u1 = RandomNumber(1.0);
    double u2 = RandomNumber(1.0);
    if (u1 == 0.0)
    {
        u1 = 1e-4;
    }
    return sqrt(-2.0*log(u1))*cos(2*RN_PI*u2)*sigma + mean;
}

bool MathUtil::
AcceptAccordingToRate(double acceptRate)
{
    double rand = RandomNumber(1.0);
    if (rand <= acceptRate) return true;
    return false;
}

int MathUtil::
Power(int base, int exp)
{
	if (base>10 && exp>10) return -1;
	int prod = 1;
	for (int i=0; i<exp; i++) {
		prod *= base;
	}
	return prod;
}

/*convert an integer (index) to an array with num_digits(N) digits, each
 digit is 0~max_per_digit(M)-1
 the range of integer is (0 ~ pow(M,N)-1)*/
const vector<int> MathUtil::
Integer2MNaryArray(int num_digits, int max_per_digit, int index)
{
	vector<int> array(num_digits, 0);
	for (int i=0; i<num_digits; i++) {
		array[i] = index % max_per_digit;
		index = index / max_per_digit;
	}
	assert(index == 0);
	return array;
}

const vector<int> MathUtil::
RandomSubset(int target_sz, int total_sz)
{
//	printf("Beigin random subset ...\n");
	assert(target_sz <= total_sz);
	vector<bool> visited_flag(total_sz, false);
	vector<int> subset;
	while (int(subset.size()) < target_sz) {
		int rand = RandomInt(total_sz);
		if (visited_flag[rand]) {
			while (visited_flag[rand]) {
				rand = (rand + 1)%total_sz;
			}
		}
		subset.push_back(rand);
		visited_flag[rand] = true;
	}
//	printf("end random subset!\n");
	return subset;
}



bool MathUtil::
IsNaN(double val)
{
    return (val != val);
}

bool MathUtil::
IsInf(double val)
{
    return std::numeric_limits<double>::has_infinity &&
    val == std::numeric_limits<double>::infinity();
}

// targetNum is the target number of items we want to end up with
const vector< vector<int> > MathUtil::
EnumerateSubset(const vector<int>& pool, int size, int targetNum, int startIdx)
{
    if (targetNum == 0) {
        vector<int> array;
        vector<vector<int> > returnArrays;
        returnArrays.push_back(array);
        return returnArrays;
    }
    int maxIdx = pool.size() - targetNum;
    assert(maxIdx >= startIdx);
    vector<vector<int> > returnArrays;
    for (int i=startIdx; i<=maxIdx; i++) {
        vector<vector<int> > ansArrays = EnumerateSubset(pool, size-1, targetNum-1, i+1);
        for (int j=0; j<(int)ansArrays.size(); j++) {
            ansArrays[j].push_back(pool[i]);
            returnArrays.push_back(ansArrays[j]);
        }
    }
    return returnArrays;
}

void MathUtil::
EnumerateSubsetInFlags(vector<int>& curFlags, vector< std::vector<int> >& subsetArrayInFlags,
                       const vector<int>& candFlags, int startIdx)
{
    if (startIdx >= (int)curFlags.size()) {
        subsetArrayInFlags.push_back(curFlags);
    }
    else {
        for (int i=0; i<(int)candFlags.size(); i++) {
            curFlags[startIdx] = candFlags[i];
            EnumerateSubsetInFlags(curFlags, subsetArrayInFlags, candFlags, startIdx+1);
        }
    }
}

int MathUtil::
Choose(int numCands, int numSelected)
{
    if (numCands<numSelected) return 0;
    int prod = 1;
    for (int x=numCands; x>numCands-numSelected; x--) {
        prod *= x;
    }
    for (int x=1; x<=numSelected; x++) {
        prod /= x;
    }
    return prod;
}

// begin with root node, and end with leaf nodes
const vector<int> MathUtil::
ComputeTopologicalOrder(const vector< pair<int,int> >& edges)
{
    vector<int> visitedNodeArray;
    set<int> visitedNodeSet;
    int pointer = 0;
    vector<bool> edgeDiscardedFlags(edges.size(), false);
    // map<pair<int,int>,int> edgeIdxMap;
    map<int, vector<int> > outgoingEdgeIDs;
    map<int, vector<int> > incomingEdgeIDs;
    set<int> nodeArray;
    for (int i=0; i<(int)edges.size(); i++) {
        // edgeIdxMap[edges[i]] = i;
        outgoingEdgeIDs[edges[i].first].push_back(i);
        incomingEdgeIDs[edges[i].second].push_back(i);
        nodeArray.insert(edges[i].first);
        nodeArray.insert(edges[i].second);
    }
    
    // initialize visited node array
    for (set<int>::const_iterator it=nodeArray.begin();
         it!=nodeArray.end(); it++) {
        int node = *it;
        if (incomingEdgeIDs.find(node) == incomingEdgeIDs.end()) {
            visitedNodeArray.push_back(node);
            visitedNodeSet.insert(node);
        }
    }
    while (pointer < visitedNodeArray.size()) {
        int node = visitedNodeArray[pointer];
        pointer ++;
        if (outgoingEdgeIDs.find(node) == outgoingEdgeIDs.end()) continue;
        // go through all outgoing edges,
        // and detect candidates to add into visited
        vector<int> edgeIDs = outgoingEdgeIDs[node];
        vector<int> toCheckNodes;
        for (int i=0; i<(int)edgeIDs.size(); i++) {
            pair<int,int> edge = edges[edgeIDs[i]];
            assert(edge.first == node);
            edgeDiscardedFlags[edgeIDs[i]] = true;
            toCheckNodes.push_back(edge.second);
        }
        for (int i=0; i<(int)toCheckNodes.size(); i++) {
            int candNode = toCheckNodes[i];
            // assert the node hasn't been added yet
            assert(visitedNodeSet.find(candNode) == visitedNodeSet.end());
            vector<int> inEdgeIDs = incomingEdgeIDs[candNode];
            bool allRemoved = true;
            for (int j=0; j<(int)inEdgeIDs.size(); j++) {
                if (!edgeDiscardedFlags[inEdgeIDs[j]]) {
                    allRemoved = false;
                    break;
                }
            }
            if (allRemoved) visitedNodeArray.push_back(candNode);
        }
    }
    bool allRemoved = true;
    for (int i=0; i<(int)edgeDiscardedFlags.size(); i++) {
        if (!edgeDiscardedFlags[i]) {
            allRemoved = false;
            break;
        }
    }
    if (!allRemoved) {
        fprintf(stderr, "MathUtil::ComputeTopologicalOrder some edges are not removed in the end!\n");
    }
    return visitedNodeArray;
}

int MathUtil::
Factorial(int k)
{
    int prod = 1;
    for (int i=2; i<=k; i++)
        prod *= i;
    return prod;
}

double MathUtil::
KernelTriangular(double u)
{
    if (u <= 1 && u >= 0) return 1-u;
    else if (u >= -1 && u < 0) return 1+u;
    else return 0;
}

double MathUtil::
KernelGaussian(double u)
{
    return 0.39894228*fastMinusExp(0.5*u*u);
}

double MathUtil::
KernelGaussianInLogSpace(double u)
{
    return 0.5*u*u + 0.9189385332;
}

/** Computes a fast approximation to exp(-x). */
double MathUtil::
fastMinusExp(double x)
{
    return exp(-x);
    //return fastMinuzExpWider_1(x);
}

// widen up fastMinuzExp
float MathUtil::
fastMinuzExpWider_1(float x)
{
    bool lessZero = false;
    
    if (x < 0)
    {
        lessZero = true;
        x = -x;
    }
    
    int mult = 0;
    
    while (x > 0.69 * 2 * 2 * 2 * 2 * 2 * 2)
    {
        mult += 6;
        x /= 64.0f;
    }
    
    while (x > 0.69 * 2 * 2 * 2)
    {
        mult += 3;
        x /= 8.0f;
    }
    
    while (x > 0.69 * 2 * 2)
    {
        mult += 2;
        x /= 4.0f;
    }
    
    while (x > 0.69)
    {
        mult++;
        x /= 2.0f;
    }
    
    x = fastMinuzExp_1(x);
    
    while (mult)
    {
        mult--;
        x = x * x;
    }
    
    if (lessZero)
    {
        return 1 / x;
    }
    else
    {
        return x;
    }
}

float MathUtil::
fastMinuzExp_1(float x)
{
    // err <= 3e-3
    return (float)(1
                   - x * (0.9664
                          - x * (0.3536)));
}
