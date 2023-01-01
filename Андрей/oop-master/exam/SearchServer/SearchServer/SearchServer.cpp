#include "SearchServer.h"

SearchServer::SearchServer()
{
	m_docs = {};
	m_docsCount = 0;
}

int SearchServer::GetDocsCount() const
{
	return m_docsCount;
}

void SearchServer::AddDoc(const std::string& doc)
{
	if (doc.empty())
	{
		return;
	}

	m_docs.insert(std::pair<int, std::string>(m_docsCount, doc));

	m_docsCount++;
}

std::vector<int> SearchServer::FindDocs(const std::string& query) const
{
	if (query.empty())
	{
		return {};
	}

	std::vector<int> result;

	std::set<std::string> querySet = MakeSetOfQuery(query);

	for (auto docs : m_docs)
	{
		int entrys = FindEntryCountInDoc(docs.second, querySet);

		if (entrys > 0)
		{
			result.push_back(docs.first);
		}
	}

	return result;
}

std::vector<SearchServer::Doc> SearchServer::FindDocsWithRelevance(const std::string& query) const
{
	if (query.empty())
	{
		return {};
	}

	std::vector<Doc> result;

	std::set<std::string> querySet = MakeSetOfQuery(query);

	for (auto docs : m_docs)
	{
		int entrys = FindEntryCountInDoc(docs.second, querySet);

		if (entrys > 0)
		{
			result.push_back({docs.first, entrys});
		}
	}

	std::sort(result.begin(), result.end(), [](const Doc& docResult1, const Doc& docResult2) { return docResult1.relevance > docResult2.relevance; });
	
	return result;
}

int SearchServer::FindEntryCountInDoc(const std::string& source, const std::set<std::string>& querySet) const
{
	int entrys = 0;

	std::string part;
	std::istringstream iss(source);

	while (iss >> part)
	{
		if (querySet.find(part) != querySet.end())
		{
			++entrys;
		}
	}

	return entrys;
}

std::set<std::string> SearchServer::MakeSetOfQuery(const std::string& query) const
{
	std::string part;
	std::istringstream iss(query);

	std::set<std::string> queryParts;

	while (std::getline(iss, part, ' '))
	{
		queryParts.insert(part);
	}

	return queryParts;
}