/**
*  @file
*  @copyright defined in xmax/LICENSE
*/
#pragma once

#include <block.hpp>

namespace Xmaxplatform {
namespace Chain {

	struct block_raw
	{
		uint32_t							block_num = 0;
		xmax_type_block_id					block_id;
		signed_block_header					new_header;
		builder_rule						verifiers;
		vector<block_confirmation>			confirmations;

		uint32_t last_block_num = 0;
		uint32_t last_confired_num = 0;
		xmax_type_block_id last_confired_id;

		const xmax_type_block_id& prev_id() const
		{
			return new_header.previous;
		}

		void add_confirmation(const block_confirmation& conf, uint32_t skip);

		bool enough_confirmation() const;

	};

	struct block_pack : public block_raw
	{
		block_pack()
			: block(std::make_shared<signed_block>())
		{
		}

		signed_block_ptr	block;

		void setup(const block_pack& pre_pack, chain_timestamp when, account_name builder, const builder_rule& rule);
		void setup();
	};

	using block_pack_ptr = std::shared_ptr<block_pack>;
}
}

FC_REFLECT(Xmaxplatform::Chain::block_raw, (block_id)(new_header))

FC_REFLECT_DERIVED(Xmaxplatform::Chain::block_pack, (Xmaxplatform::Chain::block_raw), (block))

