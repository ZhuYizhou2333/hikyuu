/*
 * _Indicator.cpp
 *
 *  Created on: 2012-10-18
 *      Author: fasiondog
 */

#include <boost/python.hpp>
#include <hikyuu/indicator/Indicator.h>
#include "../_Parameter.h"
#include "../pickle_support.h"

using namespace boost::python;
using namespace hku;

Indicator (*indicator_add1)(const Indicator&, const Indicator&) = operator+;
Indicator (*indicator_sub1)(const Indicator&, const Indicator&) = operator-;
Indicator (*indicator_mul1)(const Indicator&, const Indicator&) = operator*;
Indicator (*indicator_div1)(const Indicator&, const Indicator&) = operator/;
Indicator (*indicator_mod1)(const Indicator&, const Indicator&) = operator%;
Indicator (*indicator_eq1)(const Indicator&, const Indicator&) = operator==;
Indicator (*indicator_ne1)(const Indicator&, const Indicator&) = operator!=;
Indicator (*indicator_gt1)(const Indicator&, const Indicator&) = operator>;
Indicator (*indicator_lt1)(const Indicator&, const Indicator&) = operator<;
Indicator (*indicator_ge1)(const Indicator&, const Indicator&) = operator>=;
Indicator (*indicator_le1)(const Indicator&, const Indicator&) = operator<=;
Indicator (*indicator_and1)(const Indicator&, const Indicator&) = operator&;
Indicator (*indicator_or1)(const Indicator&, const Indicator&) = operator|;

Indicator (*indicator_add2)(const Indicator&, price_t) = operator+;
Indicator (*indicator_sub2)(const Indicator&, price_t) = operator-;
Indicator (*indicator_mul2)(const Indicator&, price_t) = operator*;
Indicator (*indicator_div2)(const Indicator&, price_t) = operator/;
Indicator (*indicator_mod2)(const Indicator&, price_t) = operator%;
Indicator (*indicator_eq2)(const Indicator&, price_t) = operator==;
Indicator (*indicator_ne2)(const Indicator&, price_t) = operator!=;
Indicator (*indicator_gt2)(const Indicator&, price_t) = operator>;
Indicator (*indicator_lt2)(const Indicator&, price_t) = operator<;
Indicator (*indicator_ge2)(const Indicator&, price_t) = operator>=;
Indicator (*indicator_le2)(const Indicator&, price_t) = operator<=;
Indicator (*indicator_and2)(const Indicator&, price_t) = operator&;
Indicator (*indicator_or2)(const Indicator&, price_t) = operator|;

string (Indicator::*ind_read_name)() const = &Indicator::name;
void (Indicator::*ind_write_name)(const string&) = &Indicator::name;

void (Indicator::*setContext_1)(const Stock&, const KQuery&) = &Indicator::setContext;
void (Indicator::*setContext_2)(const KData&) = &Indicator::setContext;

Indicator (Indicator::*ind_call_1)(const Indicator&) = &Indicator::operator();
Indicator (Indicator::*ind_call_2)(const KData&) = &Indicator::operator();
Indicator (Indicator::*ind_call_3)() = &Indicator::operator();

void export_Indicator() {
    class_<Indicator>("Indicator", "技术指标", init<>())
      .def(init<IndicatorImpPtr>())
      .def(self_ns::str(self))
      .def(self_ns::repr(self))

      .add_property("name", ind_read_name, ind_write_name, "指标名称")
      .add_property("long_name", &Indicator::long_name, "返回形如：Name(param1_val,param2_val,...)")
      .add_property("discard", &Indicator::discard, "结果中需抛弃的个数")

      .def("set_discard", &Indicator::setDiscard, R"(set_discard(self, discard)
    
    设置抛弃的个数，如果小于原有的discard则无效
    :param int discard: 需抛弃的点数，大于0)")

      .def("get_param", &Indicator::getParam<boost::any>, R"(get_param(self, name)

    获取指定的参数
        
    :param str name: 参数名称
    :return: 参数值
    :raises out_of_range: 无此参数)")

      .def("set_param", &Indicator::setParam<object>, R"(set_param(self, name, value)

    设置参数

    :param str name: 参数名称
    :param value: 参数值
    :type value: int | bool | float | string | Query | KData | Stock | DatetimeList
    :raises logic_error: Unsupported type! 不支持的参数类型)")

      .def("have_param", &Indicator::haveParam, "是否存在指定参数")

      .def("empty", &Indicator::empty, "是否为空")
      .def("clone", &Indicator::clone, "克隆操作")
      .def("formula", &Indicator::formula, R"(formula(self)

    打印指标公式

    :rtype: str)")

      .def("get_result_num", &Indicator::getResultNumber, R"(get_result_num(self)

    获取结果集数量

    :rtype: int)")

      .def("get", &Indicator::get, (arg("pos"), arg("result_index") = 0))

      .def("getPos", &Indicator::getPos)

      .def("getDatetime", &Indicator::getDatetime)

      .def("get_by_date", &Indicator::getByDate, (arg("date"), arg("result_index") = 0),
           R"(get_by_date(self, date[, result_index=0])

    获取指定日期数值。如果对应日期无结果，返回 constant.null_price
 
    :param Datetime date: 指定日期
    :param int result_index: 指定的结果集
    :rtype: float)")

      .def("getResult", &Indicator::getResult)
      .def("getResultAsPriceList", &Indicator::getResultAsPriceList)
      .def("getDatetimeList", &Indicator::getDatetimeList)
      .def("setContext", setContext_1)
      .def("setContext", setContext_2)
      .def("getContext", &Indicator::getContext)
      .def("getImp", &Indicator::getImp)
      .def("__len__", &Indicator::size)
      //.def("__call__", &Indicator::operator())
      .def("__call__", ind_call_1)
      .def("__call__", ind_call_2)
      .def("__call__", ind_call_3)
#if HKU_PYTHON_SUPPORT_PICKLE
      .def_pickle(normal_pickle_suite<Indicator>())
#endif
      ;

    def("indicator_add", indicator_add1);
    def("indicator_sub", indicator_sub1);
    def("indicator_mul", indicator_mul1);
    def("indicator_div", indicator_div1);
    def("indicator_mod", indicator_mod1);
    def("indicator_eq", indicator_eq1);
    def("indicator_ne", indicator_ne1);
    def("indicator_gt", indicator_gt1);
    def("indicator_lt", indicator_lt1);
    def("indicator_ge", indicator_ge1);
    def("indicator_le", indicator_le1);
    def("indicator_and", indicator_and1);
    def("indicator_or", indicator_or1);

    def("indicator_add", indicator_add2);
    def("indicator_sub", indicator_sub2);
    def("indicator_mul", indicator_mul2);
    def("indicator_div", indicator_div2);
    def("indicator_mod", indicator_mod2);
    def("indicator_eq", indicator_eq2);
    def("indicator_ne", indicator_ne2);
    def("indicator_gt", indicator_gt2);
    def("indicator_lt", indicator_lt2);
    def("indicator_ge", indicator_ge2);
    def("indicator_le", indicator_le2);
    def("indicator_and", indicator_and2);
    def("indicator_or", indicator_or2);
}
