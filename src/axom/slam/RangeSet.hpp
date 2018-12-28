// Copyright (c) 2017-2019, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)

/**
 * \file
 *
 * \brief Basic API for an ordered set of entities in a simulation
 *
 */

#ifndef SLAM_RANGE_SET_H_
#define SLAM_RANGE_SET_H_

#include "axom/slam/OrderedSet.hpp"

namespace axom
{
namespace slam
{


/**
 * \brief Alias template for an OrderedSet whose elements belong
 * to a contiguous range \f$ \in [0,size) \f$
 * \tparam P The PositionType
 * \tparam E The ElementType
 * \sa OrderedSet
 */
template<typename P = Set::PositionType, typename E = Set::ElementType>
using PositionSet = OrderedSet<P,E>;

/**
 * \class GenericRangeSet
 * \brief Models a set whose elements belong to a contiguous range
 *  \f$ \in [lowerIndex,upperIndex) \f$
 *
 * \details The ElementType here needs to be computable as offsets
 *  (of PositionType) from the lowerIndex. Examples include: signed and unsigned
 *  integral types This version of a range set still allows you to have
 * different policies on striding, indirection and subsetting
 */
template<
  typename StridingPolicy,
  typename IndirectionPolicy,
  typename SubsettingPolicy
  >
class GenericRangeSet : public OrderedSet<
    Set::PositionType,
    Set::ElementType,
    policies::RuntimeSize<Set::PositionType>,
    policies::RuntimeOffset<Set::PositionType>,
    StridingPolicy,
    IndirectionPolicy,
    SubsettingPolicy >
{

private:
  typedef OrderedSet<
      Set::PositionType,
      Set::ElementType,
      policies::RuntimeSize<Set::PositionType>,
      policies::RuntimeOffset<Set::PositionType>,
      StridingPolicy,
      IndirectionPolicy,
      SubsettingPolicy                                     > OrderedSetType;

  static const typename OrderedSetType::PositionType DEFAULT_SIZE =
    OrderedSetType::SizePolicyType::DEFAULT_VALUE;
  static const typename OrderedSetType::PositionType DEFAULT_OFFSET =
    OrderedSetType::OffsetPolicyType::DEFAULT_VALUE;
  static const typename OrderedSetType::PositionType DEFAULT_STRIDE =
    OrderedSetType::StridePolicyType::DEFAULT_VALUE;

public:
  typedef typename OrderedSetType::PositionType PositionType;
  typedef typename OrderedSetType::IndexType IndexType;
  typedef typename OrderedSetType::ElementType ElementType;

public:
  GenericRangeSet(PositionType size = DEFAULT_SIZE)
    : OrderedSetType(size, DEFAULT_OFFSET, DEFAULT_STRIDE) {}

  GenericRangeSet(const typename OrderedSetType::SetBuilder & builder)
    : OrderedSetType(builder) {}

  GenericRangeSet(PositionType lowerIndex, PositionType upperIndex)
    : OrderedSetType(upperIndex - lowerIndex, lowerIndex,DEFAULT_STRIDE) {}
};


/**
 * \class RangeSet
 *
 * \brief Models a set whose elements belong to a contiguous range
 *  \f$ \in [lowerIndex,upperIndex) \f$
 *
 * \details The ElementType here needs to be computable as offsets (of
 *  PositionType) from the lowerIndex Examples include: signed and unsigned
 *  integral types
 */
class RangeSet : public OrderedSet<
    Set::PositionType,
    Set::ElementType,
    policies::RuntimeSize<Set::PositionType>,
    policies::RuntimeOffset<Set::PositionType> >
{

private:
  typedef OrderedSet< Set::PositionType, Set::ElementType,
                      policies::RuntimeSize<Set::PositionType>,
                      policies::RuntimeOffset<Set::PositionType>  >
    OrderedSetType;

public:
  typedef OrderedSetType::PositionType PositionType;
  typedef OrderedSetType::IndexType IndexType;
  typedef OrderedSetType::ElementType ElementType;
private:
  static const PositionType DEFAULT_SIZE =
    OrderedSetType::SizePolicyType::DEFAULT_VALUE;
  static const PositionType DEFAULT_OFFSET =
    OrderedSetType::OffsetPolicyType::DEFAULT_VALUE;
  static const PositionType DEFAULT_STRIDE =
    OrderedSetType::StridePolicyType::DEFAULT_VALUE;


public:
  RangeSet(PositionType size = DEFAULT_SIZE)
    : OrderedSetType(size, DEFAULT_OFFSET, DEFAULT_STRIDE) {}

  RangeSet(PositionType lowerIndex, PositionType upperIndex)
    : OrderedSetType(upperIndex - lowerIndex, lowerIndex,DEFAULT_STRIDE) {}

  RangeSet(const OrderedSetType::SetBuilder & builder) : OrderedSetType(builder)
  {}

};


} // end namespace slam
} // end namespace axom

#endif //  SLAM_RANGE_SET_H_
