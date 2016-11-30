/*
 * PReduceFFNode.hpp
 *
 *  Created on: Nov 11, 2016
 *      Author: misale
 */

#ifndef INTERNALS_FFOPERATORS_PREDUCEFFNODE_HPP_
#define INTERNALS_FFOPERATORS_PREDUCEFFNODE_HPP_

#include <ff/node.hpp>
#include "../Types/KeyValue.hpp"
#include "../utils.hpp"
#include <map>

using namespace ff;


template<typename In>
class PReduceFFNode: public ff_node {
public:
	PReduceFFNode(size_t parallelism, std::function<In(In, In)>* preducef) :
			kernel(*preducef){
//#ifdef DEBUG
//					std::cerr << "[P-REDUCE-FFNODE] Constructor called\n";
//#endif
				};

	void* svc(void* task) {
//#ifdef DEBUG
//		fprintf(stderr, "[P-REDUCE-FFNODE-%p] In SVC \n", this);
//#endif
		if(task != PICO_EOS && task != PICO_SYNC){
			kv = reinterpret_cast<In*>(task);
			if(kvmap.find(kv->Key()) != kvmap.end()){
				kvmap[kv->Key()] = kernel(kvmap[kv->Key()], *kv);
			} else {
				kvmap[kv->Key()] = *kv;
			}
			delete kv;
		} else if (task == PICO_EOS) {
#ifdef DEBUG
		fprintf(stderr, "[P-REDUCE-FFNODE-%p] In SVC RECEIVED PICO_EOS \n", this);
#endif
			ff_send_out(PICO_SYNC);
			typename std::map<typename In::keytype, In>::iterator it;
			for (it=kvmap.begin(); it!=kvmap.end(); ++it){
//			#ifdef DEBUG
			//	fprintf(stderr, "[P-REDUCE-FFNODE-END-%p] <%s, %d>\n", this, (it->first).c_str(), it->second.Value());
//			#endif
				ff_send_out(new In(it->second));
			}

		}
		return GO_ON;
	}

private:
	std::function<In(In, In)> kernel;
	In* kv;
	std::map<typename In::keytype, In> kvmap;
};

#endif /* INTERNALS_FFOPERATORS_PREDUCEFFNODE_HPP_ */
