#include "Utils.h"
using namespace std;
RNBoolean FileSystemUtil::
PathExist(const string& filename)
{
    struct stat st;
    if (stat(filename.c_str(), &st) == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void FileSystemUtil::
CreateDirectory(const string& dirname)
{
    static char str[4096];
    strcpy(str, dirname.c_str());
    char* pch = strchr(str, '/');
    while (pch != NULL)
    {
        *pch = '\0';
        if (!PathExist(str))
        {
		#ifdef _MINGW//_WIN32
			mkdir(str);
		#else
            mkdir(str, 0755);
		#endif
        }
        *pch = '/';
        pch = strchr(pch+1, '/');
    }
    if (!PathExist(str))
    {
		#ifdef _MINGW//_WIN32
			mkdir(str);
		#else
            mkdir(str, 0755);
		#endif
    }
}

const vector<string> FileSystemUtil::
ListFiles(const string& dirname, const string& ext)
{
	vector<string> exts; exts.push_back(ext);
	return ListFiles(dirname, exts);
}

const vector<string> FileSystemUtil::
ListFiles(const string& dirname, const vector<string>& exts)
{
	DIR *dp;
	struct dirent *dirp;
	vector<string> files;
	if ((dp = opendir(dirname.c_str())) == NULL)
	{
		fprintf(stderr, "FileSystemUtil::ListFiles Unable to open directory %s\n", dirname.c_str());
		return files;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		string filename(dirp->d_name);
		string ext = GetExtension(filename.c_str());
		for (int i=0; i<int(exts.size()); i++)
		{
			if (ext == exts[i])
			{
				files.push_back(dirname+"/" + filename);
				break;
			}
		}
	}
	closedir(dp);
    // rank files by name
    StringUtil::BubbleSort(files);
	return files;
}

string FileSystemUtil::
GetExtension(const string& str)
{
	string::size_type idx = str.rfind('.');
	if (idx != string::npos)
	{
		return str.substr(idx+1);
	}
	return string("");
}

string FileSystemUtil::
GetBasename(const string& filename, RNBoolean with_ext)
{
	vector<string> segments = StringUtil::Split(filename, '/');
	string basename = segments[segments.size() - 1];
	if (!with_ext) {
		string::size_type idx = basename.rfind('.');
		if (idx != string::npos) {
			return basename.substr(0, idx);
		}
	}
	return basename;
}


std::string FileSystemUtil::
GetDirname(const std::string& filename)
{
    vector<string> segments = StringUtil::Split(filename, '/');
    segments.erase(segments.begin() + segments.size() - 1);
    return StringUtil::Join(segments, '/');
}

void FileSystemUtil::
Copy(const string& src, const string& dst)
{
	// system call
	string cmd("cp ");
	cmd = cmd + src+ " "+dst;
	system(cmd.c_str());
}

void FileSystemUtil::
CopyDir(const string& src, const string& dst)
{
    string cmd("cp -R ");
    cmd = cmd + src+ "/* "+dst;
    system(cmd.c_str());
}

void FileSystemUtil::
Delete(const string& pathname)
{
	// systm call
	string cmd("rm -fr ");
	cmd = cmd + pathname;
	system(cmd.c_str());
}

void FileSystemUtil::
Execute(const string& cmd)
{
    printf("FileSystemUtil::Execute executing %s ...\n", cmd.c_str());
    system(cmd.c_str());
}

void FileSystemUtil::
WaitInput(void)
{
    printf("Please press any key to continue!\n");
    getchar();
}
