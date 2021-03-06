/**
 * @file
 * @copyright  Copyright 2016 GNSS Sensor Ltd. All right reserved.
 * @author     Sergey Khabarov - sergeykhbr@gmail.com
 * @brief      CPU Fetch Instruction stage.
 */

#ifndef __DEBUGGER_RIVERLIB_FETCH_H__
#define __DEBUGGER_RIVERLIB_FETCH_H__

#include <systemc.h>
#include "../river_cfg.h"

namespace debugger {

SC_MODULE(InstrFetch) {
    sc_in<bool> i_clk;
    sc_in<bool> i_nrst;
    sc_in<bool> i_pipeline_hold;
    sc_in<bool> i_mem_req_ready;
    sc_out<bool> o_mem_addr_valid;
    sc_out<sc_uint<BUS_ADDR_WIDTH>> o_mem_addr;
    sc_in<bool> i_mem_data_valid;
    sc_in<sc_uint<BUS_ADDR_WIDTH>> i_mem_data_addr;
    sc_in<sc_uint<32>> i_mem_data;
    sc_in<bool> i_mem_load_fault;
    sc_out<bool> o_mem_resp_ready;

    sc_in<sc_uint<BUS_ADDR_WIDTH>> i_e_npc;
    sc_in<sc_uint<BUS_ADDR_WIDTH>> i_predict_npc;
    sc_in<bool> i_minus2;
    sc_in<bool> i_minus4;

    sc_out<bool> o_mem_req_fire;                    // used by branch predictor to form new npc value
    sc_out<bool> o_ex_load_fault;
    sc_out<bool> o_valid;
    sc_out<sc_uint<BUS_ADDR_WIDTH>> o_pc;
    sc_out<sc_uint<32>> o_instr;
    sc_out<bool> o_hold;                                // Hold due no response from icache yet
    sc_in<bool> i_br_fetch_valid;                       // Fetch injection address/instr are valid
    sc_in<sc_uint<BUS_ADDR_WIDTH>> i_br_address_fetch;  // Fetch injection address to skip ebreak instruciton only once
    sc_in<sc_uint<32>> i_br_instr_fetch;                // Real instruction value that was replaced by ebreak
    sc_out<sc_biguint<DBG_FETCH_TRACE_SIZE*64>> o_instr_buf;               // todo: remove it

    void comb();
    void registers();

    SC_HAS_PROCESS(InstrFetch);

    InstrFetch(sc_module_name name_);

    void generateVCD(sc_trace_file *i_vcd, sc_trace_file *o_vcd);

 private:
    struct RegistersType {
        sc_signal<bool> wait_resp;
        sc_signal<sc_uint<5>> pipeline_init;
        sc_signal<sc_uint<BUS_ADDR_WIDTH>> pc_z1;
        sc_signal<sc_uint<BUS_ADDR_WIDTH>> raddr_not_resp_yet;
        sc_signal<sc_uint<BUS_ADDR_WIDTH>> br_address;
        sc_signal<sc_uint<32>> br_instr;
        sc_signal<sc_biguint<DBG_FETCH_TRACE_SIZE*64>> instr_buf;

        sc_signal<sc_uint<BUS_ADDR_WIDTH>> resp_address;
        sc_signal<sc_uint<32>> resp_data;
        sc_signal<bool> resp_valid;
        sc_signal<sc_uint<BUS_ADDR_WIDTH>> resp_address_z;
        sc_signal<sc_uint<32>> resp_data_z;
        sc_signal<bool> minus2;
        sc_signal<bool> minus4;
    } v, r;

    void R_RESET(RegistersType &iv) {
        iv.wait_resp = 0;
        iv.pipeline_init = 0;
        iv.pc_z1 = 0;
        iv.raddr_not_resp_yet = 0;
        iv.br_address = ~0ul;
        iv.br_instr = 0;
        iv.instr_buf = 0;
        iv.resp_address = 0;
        iv.resp_data = 0;
        iv.resp_valid = 0;
        iv.resp_address_z = 0;
        iv.resp_data_z = 0;
        iv.minus2 = 0;
        iv.minus4 = 0;
    }
};


}  // namespace debugger

#endif  // __DEBUGGER_RIVERLIB_FETCH_H__
