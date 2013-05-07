#include <iostream>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
namespace units = boost::units;
namespace jotta{	
	template<typename Unit,
			 typename DataType = double
			 /*, typename StoragePolicy = console_log*/
			 >
	class result : public units::quantity<Unit,DataType> {
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
		
		bool is_valid(){
			return written_to_;
		}

		operator bool(){
			return is_valid();
		}

		std::string field(){
			return field_name_;
		}

		operator std::string(){
			return field();
		}
		
		~result(){
			if(!written_to_){
				std::cout << field_name_ <<" did not record a result." << std::endl;
			}else{
				std::cout << field_name_ << " recorded  as " << (*this) << "." << std::endl;
			}
		}
	};
}