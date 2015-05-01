#include "Utils.h"
#include <iostream>
using namespace std;
const vector<string> FileUtil::
ReadLines(const std::string& filename)
{
	vector<string> lines;
	ifstream fin(filename.c_str());
	if (!fin) return lines;
	char buffer[1024];
	while (fin.getline(buffer, 1023)) {
		if (buffer[0] == '#') continue;
		lines.push_back(buffer);
	}
	fin.close();
	return lines;
}

void FileUtil::
WriteLines(const vector<string>& lines, const string& filename)
{
    ofstream fout(filename.c_str());
    if (!fout) {
        fprintf(stderr, "FileUtil::WriteLines unable to open file %s!\n",
                filename.c_str());
        return;
    }
    for (int i=0; i<(int)lines.size(); i++)
        fout << lines[i] << std::endl;
    fout.close();
}

const R3Affine FileUtil::
ReadAffine(const std::string& filename)
{
	ifstream fin(filename.c_str());
	if (!fin) {
		printf("FileUtil::ReadAffine [Warning] unable to open file %s!\n",
				filename.c_str());
		return R3identity_affine;
	}
	vector<RNScalar> values;
	for (int i=0; i<16; i++) {
		RNScalar val;
		fin >> val;
		values.push_back(val);
	}
	fin.close();
	R4Matrix matrix(values[0], values[1], values[2], values[3],
					values[4], values[5], values[6], values[7],
					values[8], values[9], values[10], values[11],
					values[12], values[13], values[14], values[15]);
	return R3Affine(matrix);
}

void FileUtil::
WriteAffine(const R3Affine& affine, const std::string& filename)
{
	R4Matrix matrix = affine.Matrix();
	ofstream fout(filename.c_str());
	if (!fout) {
		fprintf(stderr, "FileUtil::WriteAffine unable to open file %s!\n",
				filename.c_str());
		return;
	}
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			fout<<matrix[i][j]<<" ";
		}
		fout<<std::endl;
	}
	fout.close();
}

void FileUtil::
WriteCSV(const vector< vector<string> >& data, const string& filename)
{
	ofstream fout(filename.c_str());
	if (!fout) {
		fprintf(stderr, "FileUtil::WriteCSV unable to open file %s!\n", filename.c_str());
		return;
	}
	for (int i=0; i<int(data.size()); i++) {
		for (int j=0; j<int(data[i].size()); j++) {
			string seg = data[i][j];
			// replace ',' by '_'
			size_t found = seg.find_first_of(',');
			while (found != string::npos) {
				seg[found] = '_';
				found = seg.find_first_of(',', found+1);
			}
			fout<<seg<<",";
		}
		fout<<std::endl;
	}
	fout.close();
}

void FileUtil::
WriteCSV(const vector<int>& data, const string& filename)
{
    ofstream fout(filename.c_str());
    if (!fout) {
        fprintf(stderr, "FileUtil::WriteCSV unable to open file %s!\n", filename.c_str());
        return;
    }
    for (int i=0; i<(int)data.size(); i++) {
        fout<<data[i]<<",";
    }
    fout<<std::endl;
    fout.close();
}

void FileUtil::
ImportCSV(vector<vector<string> >& data, const string& filename)
{
    ifstream fin(filename.c_str());
    if (!fin) {
        fprintf(stderr, "FileUtil::ImportCSV unable to open file %s!\n", filename.c_str());
        return;
    }
    string buffer;
    while (!std::getline(fin, buffer, '\n').eof()) {
        string content = StringUtil::Trim(buffer, " ");
        vector<string> segs = StringUtil::Split(content, ',');
        data.push_back(segs);
    }
    fin.close();
}

R3TriangleArray * FileUtil::
ReadMesh(const string& filename)
{
    // Open file
    RNArray<R3TriangleVertex *> vertices;
    RNArray<R3Triangle *> triangles;
	FILE *fp;
	if (!(fp = fopen(filename.c_str(), "r")))
	{
		std::cout<<"[ERROR] Unable to open (read) "<<filename<<std::endl;
		assert(false);
	}
	
	// Read file
	int nverts = 0;
	int nfaces = 0;
	int nedges = 0;
	int line_count = 0;
	int vertex_count = 0;
	int face_count = 0;
	char buffer[1024];
	char header[64];
	while (fgets(buffer, 1023, fp)) {
		// Increment line counter
		line_count++;
		
		// Skip white space
		char *bufferp = buffer;
		while (isspace(*bufferp)) bufferp++;
		
		// Skip blank lines and comments
		if (*bufferp == '#') continue;
		if (*bufferp == '\0') continue;
		
		// Check section
		if (nverts == 0) {
			// Read header keyword
			if (strstr(bufferp, "OFF")) {
				// Check if counts are on first line
				int tmp;
				if (sscanf(bufferp, "%s%d%d%d", header, &tmp, &nfaces, &nedges) == 4) {
					nverts = tmp;
				}
			}
			else {
				// Read counts from second line
				if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3)) {
					std::cout<<"[ERROR] Unable to read header "<<line_count;
					std::cout<<" file="<<filename<<std::endl;
					fclose(fp);
					assert(false);
				}
			}
		}
		else if (vertex_count < nverts) {
			// Read vertex coordinates
			double x, y, z;
			if (sscanf(bufferp, "%lf%lf%lf", &x, &y, &z) != 3) {
				std::cout<<"[ERROR] Unable to read vtx coords "<<line_count;
				std::cout<<" file="<<filename<<std::endl;
				fclose(fp);
				assert(false);
			}
			
			// Create vertex
            R3Point position(x, y, z);
            R3TriangleVertex* vertex = new R3TriangleVertex(position);
            vertices.Insert(vertex);
			// Increment counter
			vertex_count++;
		}
		else if (face_count < nfaces) {
			// Read number of vertices in face
			int face_nverts = 0;
			bufferp = strtok(bufferp, " \t");
			if (bufferp) face_nverts = atoi(bufferp);
			else {
				std::cout<<"[ERROR] Unable to read face "<<line_count;
				std::cout<<" file="<<filename<<std::endl;
				fclose(fp);
				assert(false);
			}
			
			// Read vertex indices for face
			bufferp = strtok(NULL, " \t");
			assert(bufferp);
			int v1 = atoi(bufferp);
			bufferp = strtok(NULL, " \t");
			assert(bufferp);
			int v2 = atoi(bufferp);
			bufferp = strtok(NULL, " \t");
			assert(bufferp);
			int v3 = atoi(bufferp);
            R3Triangle* face = new R3Triangle(vertices.Kth(v1),
                                              vertices.Kth(v2),
                                              vertices.Kth(v3));
            triangles.Insert(face);
			// Increment counter
			face_count++;
		}
		else {
			// Should never get here
			std::cout<<"[ERROR] extr text line "<<line_count;
			std::cout<<" file="<<filename<<std::endl;
			assert(false);
		}
	}
	
	// Close file
	fclose(fp);
    return new R3TriangleArray(vertices, triangles);
}

