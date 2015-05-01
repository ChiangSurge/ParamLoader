#pragma once
namespace FileUtil
{
	const std::vector<std::string> ReadLines(const std::string& filename);
    void WriteLines(const std::vector<std::string>& lines, const std::string& filename);
	// affine
    const R3Affine ReadAffine(const std::string& filename);
	void WriteAffine(const R3Affine& affine, const std::string& filename);
	// csv
    void WriteCSV(const std::vector< std::vector<std::string> >& data, const std::string& filename);
    void WriteCSV(const std::vector<int>& data, const std::string& filename);
    void ImportCSV(std::vector< std::vector< std::string> >& data, const std::string& filename);
    // mesh
    R3TriangleArray* ReadMesh(const std::string& filename);
};