static int httpget(DWORD getdeeznuts)
{
  string url = r_lua_tostring(-1, getdeeznuts);//need tostring or tolstring for this
  Execute(DownloadURL(url));//download url (replace Execute() with your exec function)
  return getdeeznuts;//what
}

//TODO: register httpget() inside of lua enviroment

//main url functions (DONT TOUCH)!

#include <Windows.h>
#include <string>
#include <WinInet.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wininet.lib")

std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;//dont use NULL becuz homo
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);//replace
		pos += replace.length();
	}
	return subject;
}

std::string DownloadURL(const char* URL) {//URL downloader (similar to DownloadString)
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);//cmon this is homo
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {//if
		urlFile = InternetOpenUrlA(interwebs, URL, NULL, NULL, NULL, NULL);//open
		if (urlFile) {
			char buffer[2000];//buff deez nuts
			DWORD bytesRead;
			do {//do
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);//read
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);//cop
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;//return
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");//ik spliting is gay
	return p;
}
