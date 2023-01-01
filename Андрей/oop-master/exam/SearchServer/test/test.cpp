#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../SearchServer/SearchServer.h"

TEST_CASE("test functional of constructor")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}
	}
}

TEST_CASE("test functional of adding document")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}

		WHEN("add empty doc")
		{
			searchServer.AddDoc("");

			THEN("docs count = 0")
			{
				REQUIRE(searchServer.GetDocsCount() == 0);	
			}
		}

		WHEN("add 1 doc")
		{
			searchServer.AddDoc("first");

			THEN("docs count = 1")
			{
				REQUIRE(searchServer.GetDocsCount() == 1);	
			}
		}

		WHEN("add 2 doc")
		{
			searchServer.AddDoc("first");
			searchServer.AddDoc("second");

			THEN("docs count = 2")
			{
				REQUIRE(searchServer.GetDocsCount() == 2);	
			}
		}
	}
}

TEST_CASE("test functional of finding document")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}

		THEN("empty vector of finding")
		{
			REQUIRE(searchServer.FindDocs("first").empty());
		}

		WHEN("add doc first")
		{
			searchServer.AddDoc("first");

			THEN("find string second")
			{
				REQUIRE(searchServer.FindDocs("second").empty());	
			}

			THEN("find string fir")
			{
				REQUIRE(searchServer.FindDocs("fir").empty());	
			}

			THEN("find string fir")
			{
				REQUIRE(searchServer.FindDocs("").empty());	
			}

			THEN("find string first")
			{
				REQUIRE(searchServer.FindDocs("first") == std::vector<int>{0});	
			}
		}

		WHEN("add 2 doc")
		{
			searchServer.AddDoc("first second");
			searchServer.AddDoc("second third first");

			WHEN("find string first")
			{
				THEN("vector size 2")
				{
					REQUIRE(searchServer.FindDocs("first").size() == 2);
					REQUIRE(searchServer.FindDocs("first") == std::vector<int>{0, 1});
				}	
			}

			WHEN("find string third")
			{
				THEN("vector size 1")
				{
					REQUIRE(searchServer.FindDocs("third").size() == 1);
					REQUIRE(searchServer.FindDocs("third") == std::vector<int>{1});
				}	
			}

			WHEN("find string 'third third'")
			{
				THEN("vector size 1")
				{
					REQUIRE(searchServer.FindDocs("third third").size() == 1);
					REQUIRE(searchServer.FindDocs("third third") == std::vector<int>{1});
				}	
			}
		}
	}
}

TEST_CASE("test functional of finding document with relevance")
{
	GIVEN("search server")
	{
		SearchServer searchServer;

		THEN("docs count = 0")
		{
			REQUIRE(searchServer.GetDocsCount() == 0);
		}

		THEN("empty vector of finding")
		{
			REQUIRE(searchServer.FindDocsWithRelevance("first").empty());
		}

		WHEN("add doc first")
		{
			searchServer.AddDoc("first");

			THEN("find string second")
			{
				REQUIRE(searchServer.FindDocsWithRelevance("second").empty());	
			}

			THEN("find string fir")
			{
				REQUIRE(searchServer.FindDocsWithRelevance("fir").empty());	
			}

			THEN("find string first")
			{
				REQUIRE(searchServer.FindDocsWithRelevance("first").size() == 1);	
				REQUIRE(searchServer.FindDocsWithRelevance("first")[0].id == 0);	
				REQUIRE(searchServer.FindDocsWithRelevance("first")[0].relevance == 1);	
			}
		}

		WHEN("add 2 doc")
		{
			searchServer.AddDoc("first second");
			searchServer.AddDoc("second third first second");

			WHEN("find string first")
			{
				THEN("vector size 2")
				{
					REQUIRE(searchServer.FindDocsWithRelevance("first").size() == 2);
					REQUIRE(searchServer.FindDocsWithRelevance("first")[0].id == 0);
					REQUIRE(searchServer.FindDocsWithRelevance("first")[0].relevance == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("first")[1].id == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("first")[1].relevance == 1);
				}	
			}

			WHEN("find string third")
			{
				THEN("vector size 1")
				{
					REQUIRE(searchServer.FindDocsWithRelevance("third").size() == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("third")[0].id == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("third")[0].relevance == 1);
				}	
			}

			WHEN("find string 'third third'")
			{
				THEN("vector size 1")
				{
					REQUIRE(searchServer.FindDocsWithRelevance("third third").size() == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("third third")[0].id == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("third third")[0].relevance == 1);
				}	
			}

			WHEN("find string 'second'")
			{
				THEN("vector size 1")
				{
					REQUIRE(searchServer.FindDocsWithRelevance("second").size() == 2);
					REQUIRE(searchServer.FindDocsWithRelevance("second")[0].id == 1);
					REQUIRE(searchServer.FindDocsWithRelevance("second")[0].relevance == 2);
					REQUIRE(searchServer.FindDocsWithRelevance("second")[1].id == 0);
					REQUIRE(searchServer.FindDocsWithRelevance("second")[1].relevance == 1);
				}	
			}
		}
	}
}