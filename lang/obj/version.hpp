#ifndef VERSION_HPP
#define VERSION_HPP

#include <cstdio>
#include <string>
#include <iostream>

namespace Secundo
{
	class Version // Really nice: https://sourcey.com/comparing-version-strings-in-cpp/
	{
	public:
		int major = 0, minor = 0, revision = 0, build = 0;
		std::string str; // added by survari

		Version() {}

		Version(std::string version)
		{
			str = version; // added by survari
			std::sscanf(version.c_str(), "%d.%d.%d.%d", &major, &minor, &revision, &build);
		}

		bool operator < (const Version& other)
		{
			if (major < other.major)
				return true;
			if (minor < other.minor)
				return true;
			if (revision < other.revision)
				return true;
			if (build < other.build)
				return true;
			return false;
		}

		bool operator <= (const Version& other) // operator<= added by survari
		{
			if (major <= other.major)
				return true;
			if (minor <= other.minor)
				return true;
			if (revision <= other.revision)
				return true;
			if (build <= other.build)
				return true;
			return false;
		}

		bool operator > (const Version& other) // operator> added by survari
		{
			if (major > other.major)
				return true;
			if (minor > other.minor)
				return true;
			if (revision > other.revision)
				return true;
			if (build > other.build)
				return true;
			return false;
		}

		bool operator == (const Version& other)
		{
			return major == other.major
				&& minor == other.minor
				&& revision == other.revision
				&& build == other.build;
		}

		friend std::ostream& operator << (std::ostream& stream, const Version& ver)
		{
			stream << ver.major;
			stream << '.';
			stream << ver.minor;
			stream << '.';
			stream << ver.revision;
			stream << '.';
			stream << ver.build;
			return stream;
		}
	};
}

#endif