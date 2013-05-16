#define SOCI_USE_BOOST
#include <iostream>
#include <boost/optional.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

namespace units = boost::units;

class sql_log{
     public:
     sql_log()
          : cursor_(soci::sqlite3,"proto.db")
     {
     }
     
     template<typename T>
     const bool record(const T& statistic){
          std::string name = statistic.field();
          typename T::primitive_type raw_data(statistic.value());
          // Round to nearest accurate soci type
          // here with intent to store everything in unique tables
          // in the meantime we say it's a double
          double data_for_recording(raw_data);
          typename T::unit_type base_unit;
          std::string unit_string = units::symbol_string(base_unit);         
          int metric_id = get_or_create_metric(name,unit_string);
          if(statistic.is_valid()){
               const bool success = log_value(data_for_recording,metric_id);          
               return true;
          }else{
               return false;
          }
     }
     
private:
     int get_or_create_metric(std::string name,std::string unit){
          boost::optional<int> id;
          cursor_<< "select id from metrics where name = :name and unit = :unit",
                    soci::into(id),soci::use(name),soci::use(unit);
          if(id.is_initialized()){
               return id.get();
          }
          cursor_ << "insert into metrics (name,unit) VALUES(:name,:unit)",
                     soci::use(name),soci::use(unit);
          cursor_ << "select id from metrics where name = :name and unit= :unit",
                     soci::into(id),soci::use(name),soci::use(unit);   
          return id.get();
     }
     
     bool log_value(double val, int id){
          cursor_ << "insert into rec_vals (metric_id,val) VALUES(:a,:b)",soci::use(id),soci::use(val);
          return true;
     }
     soci::session cursor_;
};


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
