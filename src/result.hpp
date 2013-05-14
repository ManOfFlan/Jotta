#include <iostream>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
namespace units = boost::units;

class console_log{
     public:
     console_log(std::ostream& o_stream):output_stream(o_stream){
     }
     
     template<typename T>
     const bool record(const T& statistic){
          output_stream << statistic;
          return true;     
     }
     private:
     std::ostream& output_stream;
};

class log_to_std_out : public console_log{
     public:
     log_to_std_out():console_log(std::cout){}
};


namespace jotta{	
	template<typename Unit,
			 typename DataType = double
			 , class StoragePolicy = log_to_std_out
			 /*, class FailurePolicy = record_failures_and_log */ 
			 >
	class result : public units::quantity<Unit,DataType>, public StoragePolicy {
	private:
		bool written_to_;
		const std::string field_name_;
	public:

		// constructors
		template<typename StringType>
		result(const StringType& name):field_name_(name),written_to_(false){
			
		}

		template<typename StringType>
		explicit result(const StringType& name,const units::quantity<Unit,DataType>& quant)
			: units::quantity<Unit,DataType>(quant),
			  field_name_(name),
			  written_to_(true){

		}

		template<typename StringType>
		result(const StringType& name,const DataType& raw_val)
			: units::quantity<Unit,DataType>(raw_val),
			  field_name_(name),
			  written_to_(true){
				  
		}

		// assignment/arithmetic/conversions should be dealt with
		// by quantity<>

		template<typename any>
		result& operator = (const any& val){
			units::quantity<Unit,DataType>::operator=(val);
			written_to_=true;
		}
		// Possible specialisations of the above
		// 1) Specialise for result ~ to allow us to ignore
		//  assignment to "unwritten" results
		// 2) Try and help along the compiler with different
		//    units conversions somehow
		
		bool is_valid() const {
			return written_to_;
		}
		
		std::string field() const {
			return field_name_;
		}
		
		~result(){
		     StoragePolicy::record(*this);
		}
	};
}

template<typename Unit,typename DataType,typename StoragePolicy>
std::ostream& operator << (std::ostream& out,const jotta::result<Unit,DataType,StoragePolicy>& stat){
     if(stat.is_valid()){
          out << stat.field() << " recorded as " << units::quantity<Unit,DataType>(stat) << "." << std::endl;
     }else{
          out << stat.field() << " did not record a result." << std::endl; 
     }
     return out;                                   
}
