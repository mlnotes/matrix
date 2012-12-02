#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

class matrix{
public:
    matrix(int rows, int cols);
private:
    float** data;
};






float dotproduct(std::vector<float> v1, std::vector<float> v2){
    int length = std::min(v1.size(), v2.size());
    if(length == 0) return 0;

    float sum = 0;
    for(int i = 0; i < length; ++i){
        sum += v1[i] * v2[i];
    }
    return sum;
}

vector<vector<float> > matrix_product(vector<vector<float> > m1, vector<vector<float> > m2){
    vector<vector<float> > result;
    if(m1.size() == 0 || m2.size() == 0)
        return result;

    int rows = m1.size();
    int columns = m2[0].size();
    int middle = m2.size();

    for(int i = 0; i < rows; ++i){
        result.push_back(vector<float>());
        for(int j = 0;  j < columns; ++j){
            float val = 0;
            for(int k = 0; k < middle; ++k){
                val += m1[i][k] * m2[k][j];
            }
            result[i].push_back(val);
        }
    }
    return result;
}


int main(){
    std::vector<float> v1;
    std::vector<float> v2;

    v1.push_back(1.1);
    v1.push_back(1.2);
    v1.push_back(1.3);
    v1.push_back(1.5);
    
    v2.push_back(1.1);
    v2.push_back(1.1);
    v2.push_back(1.1);

    float result = dotproduct(v1, v2);

    std::cout << result << '\n';
}
