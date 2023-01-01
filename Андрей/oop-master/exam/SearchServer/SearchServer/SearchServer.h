#pragma once
#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

class SearchServer
{
public:
	struct Doc
	{
		int id;
		int relevance;
	};

	SearchServer();

	~SearchServer() = default;

	int GetDocsCount() const;
	
	void AddDoc(const std::string& doc);

	std::vector<int> FindDocs(const std::string& query) const;

	std::vector<Doc> FindDocsWithRelevance(const std::string& query) const;

private:

	std::set<std::string> MakeSetOfQuery(const std::string& query) const;
	
	int FindEntryCountInDoc(const std::string& source, const std::set<std::string>& querySet) const;

	std::map<int, std::string> m_docs;

	int m_docsCount;
};
