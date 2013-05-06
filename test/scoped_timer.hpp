#include <boost/noncopyable.hpp>
#include <chrono>
#include <iostream>
#include <boost/format.hpp>

// Utility class for timing and logging rates
// (ie "things-per-second").
// NB _any_ destructor invokation (including early return
// from a function or exception throw) will trigger an
// output which will assume that whatever is being measured
// has completed successfully and fully.
class scoped_timer : boost::noncopyable
{
public:

  typedef std::chrono::high_resolution_clock clock_type;

  scoped_timer(
    const std::string& what,
    const std::string& units,
    double n
  )
    :_verbose(true)
    ,_what(what)
    ,_units(units)
    ,_how_many(n)
    ,_start(clock_type::now())
  {}

  double release(){
	const double t=calculate_period();
	_verbose=false;
	return t;
  }
  ~scoped_timer() {
	if(_verbose){
		const double t=calculate_period();
	    std::cout << (
	      boost::format(
	        "%1%: %|2$-5.3g| %|3$|/s (%|4$-5.3g|s)"
	      ) % _what % (_how_many/t) % _units % t
	    ) << std::endl;
	}
  }

private:
  double calculate_period(){
    clock_type::time_point stop=clock_type::now();
    const double t=1e-9*
				 std::chrono::duration_cast<std::chrono::nanoseconds>(stop-_start).count();
	return t;
  }
  bool _verbose;
  const std::string _what;
  const std::string _units;
  const double _how_many;
  const clock_type::time_point _start;
};
