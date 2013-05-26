#include "result.hpp"
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "scoped_timer.hpp"
/* Plan:
 * 	Write a use case which generates stats for
 *  dimensionless_quantity (error on number calculation)
 *  clock_cycles
 *  seconds
 *
 */

namespace si = boost::units::si;
BOOST_AUTO_TEST_CASE(result_constructor_test)
{
	jotta::result<si::absorbed_dose> unt(std::string("uninit Absd dose"));
	jotta::result<si::absorbed_dose> alt(std::string("Absd dose"));
	jotta::result<si::time> time_default(std::string("time_default"),units::quantity<si::time>(40.0*si::seconds));
	jotta::result<si::time> time_with_char("time_with_char",units::quantity<si::time>(40.0*si::seconds));
	jotta::result<si::time> hard_time("time_without_ar",12.0f*si::seconds);

	alt = -19.03* si::grays;
	// I think I'd like to be able to do this
	// but to do this - I need to be able to extract a "seconds"
	// or something similar from a si::time
	//jotta::result<si::force> deduced_unit("deduced",13.0f);
}

BOOST_AUTO_TEST_CASE(use_case_1_algorithm_bench)
{
	std::vector<float> float_array;
	{
		scoped_timer fray("float_rand_gen","112000",1.0);
		std::vector<float> float_vec(112000);
		std::generate (float_array.begin(), float_array.end(), std::rand);
		jotta::result<si::time> time_record("Floating point random gen",fray.release()*si::seconds);
		float_array = float_vec;
	}

	
	std::vector<int> int_array;
	{
		scoped_timer iray("int_rand_gen","112000",1.0);
		std::vector<int>  int_vec(112000);
		for(int i=0;i<int_vec.size();++i){
			int_vec[i] = i;
		}
		std::random_shuffle(int_array.begin(),int_array.end());
		jotta::result<si::time> time_record("Integer random gen",iray.release()*si::seconds);
		int_array = int_vec;
	}

	{
		scoped_timer fray("float_sort","112000",1.0);
		std::sort(float_array.begin(),float_array.end());
		jotta::result<si::time> time_record("Floating random sort",fray.release()*si::seconds);
	}

	{
		scoped_timer iray("int_sort","112000",1.0);
		std::sort(int_array.begin(),int_array.end());
		jotta::result<si::time> time_record("Integer random sort",iray.release()*si::seconds);
	}
}

namespace jotta{

     struct typename_conversion;


}



struct dummy_param_set{
     float sampling_rate;
     int image_dims[2];
     std::string volume_name;
     std::string hardware_arch;
     int tile_size;
     
     // how's this for syntax#
};



BOOST_AUTO_TEST_CASE(use_case_another_experiment_with_params){

     dummy_param_set params;    
     params.sampling_rate = 0.8f;
     params.image_dims[0] = 120;
     params.image_dims[1] = 512;
     params.volume_name = std::string("CT-Head");
     params.hardware_arch = std::string("AMD64");
     params.tile_size = 32;
}



BOOST_AUTO_TEST_CASE(internal_connections){

     // this is a test to ensure relations in the
     // database are working and naturally
     // tests functionality that would never be
     // in user code
JOTTA_AUTO_RUN(name_of_thing){
 // so this macro creates
 
 // JOTTA_MODULE ~ then you can scope
 // or you can add current_experiment variable
 // static class name_of_thing_experiment : public experiment{
 // and auto add the thing to current experiment 
 //    void run();
 
 //}
 
 
 // void name_of_thing_experiment::run() [/macro]

}
     
     // 1) Get tested parameter sets ~ for a particular experiment
     
     // Note: Through some hacky things, you could say that 
     // the System Environment
     // and the System Path were always parameters to the
     // test
     // then you could use this to pick up on commit number an
     // such without any real trouble
     
     
     // 2) Get "runs" for a particular parameter set
     //     (Probably storing parameters seperately so
     //        a few progressively narrowing queries? )
     
     
     
     // 3) Get "all recorded results for a particular run ? "
     //      That might be awkward    
     
     // 4) Get the run from a particular result
     
     // 5) Get the runs that test a particular parameter
     
     // 6) Get info about a run ~ Parameters, timestamp

     // 7) Get the results y that arise from a parameter x


}
