#pragma once
namespace MathUtil
{
	// Numeric computation
	RNScalar Sum(const std::vector<RNScalar>& array);
	int Sum(const std::vector<int>& array);
	RNScalar Average(const std::vector<RNScalar>& array);
    const std::vector<RNScalar> Average(const std::vector<std::vector<RNScalar> >& array, int nDims); // check array size
	RNScalar Maximum(const std::vector<RNScalar>& array, int* p = NULL);
    int Maximum(const std::vector<int>& array, int* p = NULL);
	RNScalar Minimum(const std::vector<RNScalar>& array, int* p = NULL);
    const std::vector<int> KthMaximum(const std::vector<RNScalar>& array, int k);
    const std::vector<int> KthMinimum(const std::vector<RNScalar>& array, int k);
	int Minimum(const std::vector<int>& array, int* p = NULL);
	RNScalar StandardDeviation(const std::vector<RNScalar>& array);
	RNScalar Sum(const std::vector<RNScalar>& array, const std::vector<RNScalar>& weights);
	RNScalar Average(const std::vector<RNScalar>& array, const std::vector<RNScalar>& weights);
	RNScalar StandardDeviation(const std::vector<RNScalar>& array, const std::vector<RNScalar>& weights);
    const std::vector<RNScalar> StandardDeviation(const std::vector<std::vector<RNScalar> >& array, int nDims); // check array size
    void DivideBySum(std::vector<double>& array);
	// Sorting
	void BubbleSort(std::vector<RNScalar>& values);
	void BubbleSort(const std::vector<RNScalar>& values,
					std::vector<int>& ranked_index);
	void BubbleSort(std::vector<int>& values);
	void BubbleSort(const std::vector<int>& values,
					std::vector<int>& ranked_index);
	// Set
	bool Contains(const std::vector<R3MySceneNode*>& array1,
				  const std::vector<R3MySceneNode*>& array2);
	std::vector<R3MySceneNode*> Intersect(const std::vector<R3MySceneNode*>& array1,
										  const std::vector<R3MySceneNode*>& array2);
    const std::vector<int> Intersect(const std::vector<int>& array1, const std::vector<int>& array2);
	bool IsIdenticalToSortedArray(const std::vector<int>& array1,
								  const std::vector<int>& array2);
    bool IsIdenticalToArray(const std::vector<int>& array1,
                            const std::vector<int>& array2);
	bool IsSubSetOfSortedArray(const std::vector<int>& array1,
							   const std::vector<int>& array2);
	bool IsAscendinglySorted(const std::vector<int>& array);
	bool IsSemiAscendinglySorted(const std::vector<int>& array);
	const std::vector<int> IntersectSortedArrays(const std::vector<int>& array1,
												const std::vector<int>& array2);
	// Randomization
	int RandomInt(int range);
	double RandomNumber(double range);
    double RandomNumberFromStored(double range);
    bool AcceptAccordingToRate(double acceptRate);
    void InitializeStoredRandomNumbers(int numNumbers);
    extern std::vector<double> stored_random_number_array;
	int RandomItemIndex(const std::vector<double>& probs);
	double RandomFromNormalDistribution(double mean, double sigma);
	
	// Enumeration
	/*convert an integer (index) to an array with num_digits(N) digits, each
	 digit is 0~max_per_digit(M)-1
	 the range of integer is (0 ~ pow(M,N)-1)*/
	int Power(int base, int exp);
	const std::vector<int> Integer2MNaryArray(int num_digits, int max_per_digit, int index);
	
	// Subset
	const std::vector<int> RandomSubset(int target_sz, int total_sz);
    
    // Infinity and NaN check
    bool IsNaN(double val);
    bool IsInf(double val);
    
    // enumerate subsets
    const std::vector<std::vector<int> > EnumerateSubset(const std::vector<int>& pool, int size,
                                                        int targetNum, int startIdx);
    
    void EnumerateSubsetInFlags(std::vector<int>& curFlags,
                                std::vector< std::vector<int> >& subsetArrayInFlags,
                                const std::vector<int>& candFlags, int startIdx);
    
    int Choose(int numCands, int numSelected);
    int Factorial(int k);
    // algorithm
    const std::vector<int> ComputeTopologicalOrder(const std::vector< std::pair<int,int> >& edges);
    // KDE kernels
    double KernelTriangular(double u);
    double FastExp(double y);
    double KernelGaussian(double u);
    double KernelGaussianInLogSpace(double u);
    
    // fast exp computation
    float fastMinuzExp_1(float x);
    float fastMinuzExpWider_1(float x);
    double fastMinusExp(double x);
};