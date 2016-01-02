//////////////////////////////////////////////////
/*    author huqijun ,modify time 20160102      */
//////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include<utility>
#include<functional>
#include<stdexcept>
#include<map>
#include<sstream>




//process file and build word_map
class TextQuery
{
public:
	typedef std::vector<std::string>::size_type line_no;
	/* interface:
	read_file builds internal data structures for the given file
	run_query finds the given word and returns set of lines on while it appears
	test_line return a  requested line from the input file
	file_size return the total lines of input file
	*/
	void read_file(std::ifstream & is)
	{
		store_file(is);
		build_map();
	}

	std::set<line_no> run_query(const std::string&) const;
	std::string test_line(line_no) const;
	line_no file_size() const { return  lines_of_text.size(); }

private:
	//utility function used by read_file
	void store_file(std::ifstream&);
	//associated each word with a set of line members
	void build_map();
	//vector to store input file
	std::vector<std::string> lines_of_text;
	//map word to set of lines on which it occurs
	std::map< std::string, std::set<line_no> > word_map;
};


std::set<TextQuery::line_no> TextQuery::run_query(const std::string& query_word) const
{
	std::map<std::string, std::set<line_no> >::const_iterator loc = word_map.find(query_word);
	if (loc == word_map.end())
		return std::set<line_no>();   // no found ,return a empty set
	else
		return  loc->second;
}


std::string TextQuery::test_line(line_no l) const
{
	return lines_of_text[l];
}



void TextQuery::store_file(std::ifstream&  infile)
{
	std::string temp;
	while (std::getline(infile, temp))
	{
		lines_of_text.push_back(temp);
	}

}

void TextQuery::build_map()
{

	std::string temp;
	for (line_no l = 0; l != lines_of_text.size(); ++l)
	{

		std::stringstream ss;
		ss << lines_of_text[l];
		while (ss >> temp)
		{
			if (word_map.count(temp))
			{
				word_map[temp].insert(l);
			}
			else
			{
				std::set<line_no> temp_set;
				temp_set.insert(l);
				word_map.insert(std::make_pair(temp, temp_set));
			}

		}
	}



}




void print_results(const std::set<TextQuery::line_no>& locs, const std::string & query_key, const TextQuery &tq)
{
	std::set<TextQuery::line_no>::size_type occur_times = locs.size();

	std::cout << query_key << " occurs " << occur_times << " times" << std::endl;

	for (std::set<TextQuery::line_no>::const_iterator i = locs.begin(); i != locs.end(); ++i)
	{
		std::cout << "(line " << (*i) + 1 << " ) "
			<< tq.test_line(*i) << std::endl;
	}
}







//private ,abstract class acts as a base class for concrete types
class Query_base
{
	friend  class Query;
protected:
	typedef TextQuery::line_no line_no;
	virtual ~Query_base() {}

private:
	// eval return the |set| of lines that this Query matches
	virtual std::set<line_no> eval(const TextQuery&) const = 0;

	//display prints the query
	virtual std::ostream& display(std::ostream& = std::cout) const = 0;
};


//handle class to manage Query_base inheritance hierarchy
class Query
{
	//these operators need access to the Query_base* constructor
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:

	Query(const std::string&);   //builds a new WordQuery,should be defined after class WordQuery has been defined
								 //copy control to manage pointers and use counting
	Query(const Query& c) :q(c.q), use(c.use) { ++*use; }
	~Query() { decr_use(); }
	Query& operator=(const Query&);
	std::set<TextQuery::line_no> eval(const TextQuery & t) const
	{
		return q->eval(t);
	}

	std::ostream & display(std::ostream & os) const
	{
		return q->display(os);
	}

private:
	Query(Query_base *query) :q(query), use(new std::size_t(1)) {}
	Query_base * q;
	std::size_t * use;
	void decr_use()
	{
		if (--*use == 0)
		{
			delete q;
			delete use;
		}
	}
};



Query& Query::operator=(const Query & rhs)
{
	++*rhs.use;
	decr_use();
	q = rhs.q;
	use = rhs.use;

	return *this;
}



inline std::ostream& operator<<(std::ostream& os, const Query &q)
{
	return q.display(os);
}


//derived class of Query_base,which implies the basic query function
class WordQuery : public Query_base
{
	//Query uses the WordQuery constructor
	friend class Query;
	WordQuery(const std::string &s) :query_word(s) {}
	//concrete class:WordQuery defines all inherited virtual functions
	std::set<line_no> eval(const TextQuery& t)const
	{
		return t.run_query(query_word);
	}

	std::ostream& display(std::ostream& os) const { return os << query_word; }
	std::string query_word;   ///word of which to  search
};


// Constructor of Query
Query::Query(const std::string& s):q(new WordQuery(s)),use(new std::size_t(1))
{

}






//derived class of Query_base,which implies the Not Query function
class NotQuery : public Query_base
{
	friend Query operator~(const Query&);
	NotQuery(Query q) :query(q) {}
	//concrete class:NotQuery defines all inherited virtual function
	std::set<line_no> eval(const TextQuery&) const;
	std::ostream& display(std::ostream& os) const
	{
		os << "~(" << query << ")";
		return os;
	}
	const Query query;
};

std::set<TextQuery::line_no> NotQuery::eval(const TextQuery& file) const
{
	//virtual call through the Query handle to eval
	std::set<TextQuery::line_no> has_val = query.eval(file);
	std::set<TextQuery::line_no> ret_lines;

	for (line_no i = 0; i != file.file_size(); ++i)
		if (has_val.find(i) == has_val.end())
			ret_lines.insert(i);
	return ret_lines;
}






class BinaryQuery : public Query_base
{
protected:
	BinaryQuery(Query left, Query right, std::string op) :lhs(left), rhs(right), oper(op) {}

	//abstract class:BinaryQuery doesn't define eval
	std::ostream& display(std::ostream & os) const
	{
		return os << "(" << lhs << " " << oper << " " << rhs << " " << ")";
	}


	const Query lhs, rhs;   //right and left operands
	const std::string oper;    //name of operator

};


class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query&, const Query &);
	AndQuery(Query left, Query right) :BinaryQuery(left, right, "&") {}

	//concrete class:AndQuery inherits display and defines remaining pure virtual
	std::set<line_no> eval(const TextQuery&) const;


};


//returns intersection of its operands result sets
std::set<TextQuery::line_no>  AndQuery::eval(const TextQuery& file) const
{

	//virtual calls through Query handle to get result sets for the operands
	std::set<line_no> left = lhs.eval(file),
		right = rhs.eval(file);
	std::set<line_no> ret_lines;  //destination to hold results

								  // write intersection of two ranges to a destination iterator
								  //destination iterator in this call adds element to ret

	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(ret_lines, ret_lines.begin()));

	return ret_lines;


}





class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(Query left, Query right) :BinaryQuery(left, right, "|") {}

	//concrete class:QrQuery inherits display and defines remaining pure virtual
	std::set<line_no> eval(const TextQuery&) const;
};


//returns union of its operands' results sets
std::set<TextQuery::line_no> OrQuery::eval(const TextQuery& file) const
{
	//virtual calls through Query handle to get results set for the operands
	std::set<line_no> right = rhs.eval(file),
		ret_lines = lhs.eval(file);   //destination to hold results
									  //insert the lines from that aren't already in ret_line
	ret_lines.insert(right.begin(), right.end());
	return ret_lines;
}






inline Query operator&(const Query & q1, const Query & q2)
{
	return new AndQuery(q1, q2);
}

inline Query operator|(const Query & q1, const Query & q2)
{
	return  new OrQuery(q1, q2);
}

inline Query operator~(const Query& oper)
{
	return new NotQuery(oper);
}


//function to format output
void print_results2(const std::set<TextQuery::line_no>& locs, Query& q, const TextQuery & tq)
{
	std::set<TextQuery::line_no>::size_type occur_times = locs.size();
	std::cout << "Executed Query for: ";
	q.display(std::cout);
	std::cout << std::endl;
	std::cout << "match occurs " << occur_times << " times" << std::endl;

	for (std::set<TextQuery::line_no>::const_iterator i = locs.begin(); i != locs.end(); ++i)
	{
		std::cout << "(line " << *i + 1 << ") "
			<< tq.test_line(*i) << std::endl;
	}
}


void TestSchema(TextQuery & tq)
{
	std::cout << "Exmple Query Condition:" << std::endl
				<< "Single Word Query : fuck" << std::endl
				<< "Not Query : ~fuck" << std::endl
				<< " AND Query: fuck & you" << std::endl
				<< "Or Query : fuck | you" << std::endl;
			  
	while (true)
	{
		std::cout << "Enter a condition to look for, or q to quit" << std::endl;
		std::string s;
		std::cin >> s;
		//handle user input
		if (!std::cin || s == "q")
			break;
		std::vector<std::string> svec;
		std::stringstream ss;
		ss << s;
		std::string temp;
		while (ss >> temp)
		{
			svec.push_back(temp);

		}

		std::vector<std::string>::size_type numOfOperands = svec.size();

		Query q("");
		std::set<TextQuery::line_no> locs;

		switch (numOfOperands)
		{
		case 1:
			q = Query(svec[0]);
			locs = q.eval(tq);
			print_results2(locs, q, tq);
			break;
		case 2:
			q = ~Query(svec[1]);
			locs = q.eval(tq);
			print_results2(locs, q, tq);
			break;
		case 3:
			if (svec[1] == "&")
				q = Query(svec[0]) & Query(svec[2]);
			else if (svec[1] == "|")
				q = Query(svec[0]) | Query(svec[2]);
			locs = q.eval(tq);
			print_results2(locs, q, tq);
			break;
		default:
			break;
		}


			
	}
	


}




//test code
int main()
{
	std::ifstream infile;
	infile.open("test.txt");

	TextQuery tq;
	tq.read_file(infile);



	//TestSchema(tq);



	//test TextQuery
	std::cout << "Starting Testing TextQuery class" << std::endl;
	while (true)
	{
		std::cout << "Enter a word to look for,or q to quit: " << std::endl;
		std::string s;
		std::cin >> s;
		if (!std::cin || s == "q")
			break;
		std::set<TextQuery::line_no> locs = tq.run_query(s);

		print_results(locs, s, tq);
	}

	std::cout << "Ending Testing TextQuery class" << std::endl;


	//test WordQuery
	std::cout << "Starting Testing WordQuery class" << std::endl;
	while (true)
	{
		std::cout << "Enter a word to look for ,or q to quit: " << std::endl;
		std::string s;
		std::cin >> s;
		if (!std::cin || s == "q")
			break;
		Query q(s);
		std::set<TextQuery::line_no> locs = q.eval(tq);
		print_results2(locs, q, tq);

	}

	std::cout << "Ending Testing WordQuery class" << std::endl;



	//test AndQuery
	std::cout << "Starting Testing AndQuery class" << std::endl;
	while (true)
	{
		std::cin.clear();
		std::cout << "Enter a AND condition(eg fuck & you) to look for,or q to quit: " << std::endl;
		std::string s;
		std::getline(std::cin, s);
		if (!std::cin || s == "q")
			break;
		std::stringstream ss;
		ss << s;
		std::string left, operand, right;
		ss >> left >> operand >> right;
		if (operand != "&")
		{
			std::cout << "input error ,please input again"<<std::endl;
			continue;
		}
		Query lQuery(left), rQuery(right);
		Query q = lQuery & rQuery;
		std::set<TextQuery::line_no> locs = q.eval(tq);
		print_results2(locs, q, tq);

	}


	return 0;

}

