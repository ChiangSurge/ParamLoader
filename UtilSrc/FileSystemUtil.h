#ifndef ___FILE_SYSTEM_UTIL_H
#define ___FILE_SYSTEM_UTIL_H
namespace FileSystemUtil
{
	RNBoolean PathExist(const std::string& filename);
    void CreateDirectory(const std::string& dirname);
	const std::vector<std::string> ListFiles(const std::string& dirname,
											 const std::string& ext);
	const std::vector<std::string> ListFiles(const std::string& dirname,
									   const std::vector<std::string>& exts);
	std::string GetExtension(const std::string& filename);
	std::string GetBasename(const std::string& filename, RNBoolean with_ext = TRUE);
    std::string GetDirname(const std::string& filename);
	void Copy(const std::string& src, const std::string& dst);
    void CopyDir(const std::string& src, const std::string& dst);
	void Delete(const std::string& pathname);
    void Execute(const std::string& cmd);
    // wait
    void WaitInput(void);
}
#endif