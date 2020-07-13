#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define MAX_DIRS 200
#define MAX_FILES 200

struct FileNode {
	string fileName;
};

struct DirNode {
	DirNode* parent;

	DirNode* childDirs[MAX_DIRS];
	int childDirCount;

	FileNode* childFiles[MAX_FILES];
	int childFileCount;

	string dirName;

	DirNode() {
		parent = NULL;
		childDirCount = 0;
		childFileCount = 0;
	}

	void addFile(FileNode* file) {
		for (int i = 0; i < childFileCount; i++) {
			if (file->fileName == childFiles[i]->fileName) {
				cout << "이미 존재하는 파일명 입니다." << endl;
				return;
			}
		}
		childFiles[childFileCount++] = file;
	}

	void addDir(DirNode* dir) {
		for (int i = 0; i < childDirCount; i++) {
			if (dir->dirName == childDirs[i]->dirName) {
				cout << "이미 존재하는 디렉토리명 입니다." << endl;
				return;
			}
		}
		dir->parent = this;
		childDirs[childDirCount++] = dir;
	}

	void removeFile(string filename) {
		int idx = -1;
		for (int i = 0; i < childFileCount; i++) {
			if (filename == childFiles[i]->fileName) {
				delete childFiles[i];
				idx = i;
				break;
			}
		}

		if (idx != -1) {
			for (int i = idx; i < childFileCount - 1; i++) {
				childFiles[i] = childFiles[i + 1];
			}
			childFileCount--;
		}
		else {
			cout << "해당 파일이 없습니다." << endl;
		}
	}

	void removeDir(string dirname) {
		int idx = -1;
		for (int i = 0; i < childDirCount; i++) {
			if (dirname == childDirs[i]->dirName) {
				delete childDirs[i];
				idx = i;
				break;
			}
		}

		if (idx != -1) {
			for (int i = idx; i < childDirCount - 1; i++) {
				childDirs[i] = childDirs[i + 1];
			}
			childDirCount--;
		}
		else {
			cout << "해당 디렉토리가 없습니다." << endl;
		}
	}

	void listDir(string prefix="") {
		for (int i = 0; i < childDirCount; i++) {
			cout << prefix + childDirs[i]->dirName << endl;
			childDirs[i]->listDir(prefix + childDirs[i]->dirName);
		}

		for (int i = 0; i < childFileCount; i++) {
			cout << prefix + childFiles[i]->fileName << endl;
		}
	}
};

class FileSystem {
private:
	DirNode* root;
	DirNode* currentDir;
	string absCurrentDir;

	FileNode* fileClipboard;
	DirNode* dirClipboard;

public:
	FileSystem() {
		DirNode* tmp = new DirNode();
		tmp->parent = NULL;
		tmp->childDirCount = 0;
		tmp->childFileCount = 0;
		tmp->dirName = "/";
		root = tmp;
		currentDir = root;
		absCurrentDir = "/";
		fileClipboard = NULL;
		dirClipboard = NULL;
	}

	void addFile(string filename) {
		FileNode* tmp = new FileNode();
		tmp->fileName = filename;
		currentDir->addFile(tmp);
	}

	void addDirectory(string dirname) {
		DirNode* tmp = new DirNode();
		tmp->dirName = dirname;
		currentDir->addDir(tmp);
	}

	FileNode* copyFileUtil(FileNode* srcFile) {
		FileNode* tmp = new FileNode();
		tmp->fileName = srcFile->fileName;
		return tmp;
	}

	bool copyFile(string filename) {
		//search and save
		for (int i = 0; i < currentDir->childFileCount; i++) {
			if (filename == currentDir->childFiles[i]->fileName) {
				fileClipboard = copyFileUtil(currentDir->childFiles[i]);
				return true;
			}
		}
		cout << "해당 파일이 없습니다." << endl;
		return false;
	}

	DirNode* copyDirUtil(DirNode* srcDir) {
		DirNode* tmp = new DirNode();

		tmp->childDirCount = srcDir->childDirCount;
		tmp->childFileCount = srcDir->childFileCount;
		tmp->dirName = srcDir->dirName;
		tmp->parent = srcDir->parent;

		for (int i = 0; i < tmp->childFileCount; i++) {
			tmp->childFiles[i] = copyFileUtil(srcDir->childFiles[i]);
		}

		for (int i = 0; i < tmp->childDirCount; i++) {
			tmp->childDirs[i] = copyDirUtil(srcDir->childDirs[i]);
		}
		return tmp;
	}

	bool copyDir(string dirname) {
		for (int i = 0; i < currentDir->childDirCount; i++) {
			if (dirname == currentDir->childDirs[i]->dirName) {
				dirClipboard = copyDirUtil(currentDir->childDirs[i]);
				return true;
			}
		}
		cout << "해당 디렉토리가 없습니다." << endl;
		return false;
	}

	void pasteFile() {
		if (fileClipboard == NULL)
			return;
		currentDir->addFile(fileClipboard);
		fileClipboard = NULL;
	}

	void pasteDir() {
		if (dirClipboard == NULL)
			return;
		currentDir->addDir(dirClipboard);
		dirClipboard = NULL;
	}

	void removeFile(string filename) {
		currentDir->removeFile(filename);
	}

	void removeDir(string dirname) {
		currentDir->removeDir(dirname);
	}

	void cutFile(string filename) {
		if (copyFile(filename)) {
			removeFile(filename);
		}
	}

	void cutDir(string dirname) {
		if (copyDir(dirname)) {
			removeDir(dirname);
		}
		else {
			cout << "해당 디렉토리가 없습니다." << endl;
		}
	}

	string updateAbsDir() {
		DirNode* tmpParent = currentDir->parent;
		string absPath = currentDir->dirName;

		while (tmpParent != NULL) {
			absPath = tmpParent->dirName + absPath;
			tmpParent = tmpParent->parent;
		}
		return absPath;
	}

	void changeDir(string dirname){
		// change dir from currentDir
		int idx = -1;
		if (dirname == "../") {
			currentDir = currentDir->parent;
			absCurrentDir = updateAbsDir();
		}
		else {
			for (int i = 0; i < currentDir->childDirCount; i++) {
				if (currentDir->childDirs[i]->dirName == dirname) {
					idx = i;
					break;
				}
			}
			if (idx != -1) {
				currentDir = currentDir->childDirs[idx];
				absCurrentDir = updateAbsDir();
			}
		}
	}

	void listDir() {
		currentDir->listDir();
	}

	friend ostream& operator<< (ostream& out, const FileSystem& fs);
};

ostream& operator<< (ostream& out, const FileSystem& fs) {
	out << fs.absCurrentDir << "> ";
	return out;
}

void promptCLI(vector<string>& tokens)
{
	string command;
	string ctok;

	getline(cin, command);
	stringstream sscmd(command);
	while (getline(sscmd, ctok, ' '))
	{
		tokens.push_back(ctok);
	}
	return;
}

int main()
{
	vector<string> tokens;
	FileSystem fs;

	while (true)
	{
		cout << fs;
		promptCLI(tokens);
		/* Do something */
		if (tokens.size() == 2) {
			if (tokens[0] == "add") {
				if (tokens[1][tokens[1].length() - 1] == '/') {
					fs.addDirectory(tokens[1]);
				}
				else {
					fs.addFile(tokens[1]);
				}
			}
			else if (tokens[0] == "cd") {
				if (tokens[1][tokens[1].length() - 1] == '/') {
					fs.changeDir(tokens[1]);
				}
			}
			else if (tokens[0] == "cut") {
				if (tokens[1][tokens[1].length() - 1] == '/') {
					fs.cutDir(tokens[1]);
				}
				else {
					fs.cutFile(tokens[1]);
				}
			}
			else if (tokens[0] == "rm") {
				if (tokens[1][tokens[1].length() - 1] == '/') {
					fs.removeDir(tokens[1]);
				}
				else {
					fs.removeFile(tokens[1]);
				}
			}
			else if (tokens[0] == "copy") {
				if (tokens[1][tokens[1].length() - 1] == '/') {
					fs.copyDir(tokens[1]);
				}
				else {
					fs.copyFile(tokens[1]);
				}
			}

		}
		else if(tokens.size() == 1){
			/* Do something */
			if (tokens[0] == "ls") {
				fs.listDir();
			}
			else if (tokens[0] == "paste") {
				fs.pasteDir();
				fs.pasteFile();
			}
			else if (tokens[0] == "exit") {
				break;;
			}
		}
		if (tokens.size() > 0)
			tokens.clear();
	}
}