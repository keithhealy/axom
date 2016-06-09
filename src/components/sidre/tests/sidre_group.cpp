/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and
 * further review from Lawrence Livermore National Laboratory.
 */

#include "gtest/gtest.h"
#include <cstring>

#include "sidre/sidre.hpp"

using asctoolkit::sidre::SidreLength;
using asctoolkit::sidre::TypeID;
using asctoolkit::sidre::DataBuffer;
using asctoolkit::sidre::DataGroup;
using asctoolkit::sidre::DataStore;
using asctoolkit::sidre::DataView;
using asctoolkit::sidre::IndexType;
using asctoolkit::sidre::InvalidIndex;
using asctoolkit::sidre::nameIsValid;
using asctoolkit::sidre::indexIsValid;
using asctoolkit::sidre::DataType;
using asctoolkit::sidre::INT_ID;
using asctoolkit::sidre::FLOAT64_ID;

// API coverage tests
// Each test should be documented with the interface functions being tested

//------------------------------------------------------------------------------
// getName()
//------------------------------------------------------------------------------
TEST(sidre_group,get_name)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  DataGroup * group = root->createGroup("test");

  EXPECT_TRUE(group->getName() == std::string("test") );

  DataGroup * group2 = root->getGroup("foo");
  EXPECT_TRUE(group2 == ATK_NULLPTR);
}

//------------------------------------------------------------------------------
// getNameWithPath()
//------------------------------------------------------------------------------
TEST(sidre_group,get_group_with_path)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  // Test full path access when building incrementally
  DataGroup * group =
    root->createGroup("test1")->createGroup("test2")->createGroup("test3");
  DataGroup * group2 = root->getGroup("test1/test2/test3");

  EXPECT_TRUE(ATK_NULLPTR != group2);
  EXPECT_EQ(group, group2);

  // Test incremental access when building full path
  DataGroup * groupP = root->createGroup("testA/testB/testC");
  DataGroup * groupP2 =
    root->getGroup("testA")->getGroup("testB")->getGroup("testC");

  EXPECT_TRUE(ATK_NULLPTR != groupP2);
  EXPECT_EQ(groupP, groupP2);


  // Now verify that code will not create missing groups.
  // TODO - improve error handling so this isn't fatal.
//  DataGroup * group3 = root->createGroup("testa")->createGroup("testb")->createGroup("testc");
//  DataGroup * group_bad = root->getGroup("testa/BAD/testc");

//  (void)group3;

//  EXPECT_EQ(group_bad, root->getGroup("testa") );

  delete ds;

}


//------------------------------------------------------------------------------
// getParent()
//------------------------------------------------------------------------------
TEST(sidre_group,get_parent)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  DataGroup * parent = root->createGroup("parent");
  DataGroup * child = parent->createGroup("child");

  EXPECT_TRUE( child->getParent() == parent );

  delete ds;
}

//------------------------------------------------------------------------------
// Verify getDatastore()
//------------------------------------------------------------------------------
TEST(sidre_group,get_datastore)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  DataGroup * group = root->createGroup("parent");

  EXPECT_TRUE( group->getDataStore() == ds );

  DataStore const * const_ds = group->getDataStore();
  EXPECT_TRUE( const_ds == ds );

  delete ds;
}

//------------------------------------------------------------------------------
// Verify getGroup()
//------------------------------------------------------------------------------
TEST(sidre_group,get_group)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  DataGroup * parent = root->createGroup("parent");
  DataGroup * child = parent->createGroup("child");
  EXPECT_TRUE( child->getParent() == parent );

  EXPECT_TRUE( parent->getGroup("child") == child );
  // check error condition
  EXPECT_TRUE( parent->getGroup("non-existant group") == ATK_NULLPTR );

  delete ds;
}

//------------------------------------------------------------------------------
// Verify getView()
//------------------------------------------------------------------------------
TEST(sidre_group,get_view)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  DataGroup * parent = root->createGroup("parent");
  DataView * view = parent->createView("view");

  EXPECT_TRUE( parent->getView("view") == view );

  // check error condition
  EXPECT_TRUE( parent->getView("non-existant view") == ATK_NULLPTR );

  delete ds;
}
//------------------------------------------------------------------------------
// Verify getViewWithPath()
//------------------------------------------------------------------------------
TEST(sidre_group,get_view_with_path)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  // Test with full path access when building incrementally
  DataView * view =
    root->createGroup("group1")->createGroup("group2")->createView("view1");
  DataView * view2 = root->getView("group1/group2/view1");

  EXPECT_TRUE(ATK_NULLPTR != view2);
  EXPECT_EQ( view, view2 );


  // Test incremental access when building with full path
  DataView * viewP = root->createView("groupA/groupB/viewA");
  DataView * viewP2 =
    root->getGroup("groupA")->getGroup("groupB")->getView("viewA");

  EXPECT_TRUE(ATK_NULLPTR != viewP2);
  EXPECT_EQ( viewP, viewP2 );

  delete ds;
}


//------------------------------------------------------------------------------
// Verify getViewName(), getViewIndex()
//------------------------------------------------------------------------------
TEST(sidre_group,get_view_names_and_indicies)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  DataGroup * parent = root->createGroup("parent");
  DataView * view1 = parent->createView("view1");
  DataView * view2 = parent->createView("view2");

  EXPECT_EQ(parent->getNumViews(), 2u);

  IndexType idx1 = parent->getViewIndex("view1");
  IndexType idx2 = parent->getViewIndex("view2");

  const std::string& name1 = parent->getViewName(idx1);
  const std::string& name2 = parent->getViewName(idx2);

  EXPECT_EQ(name1, std::string("view1"));
  EXPECT_EQ(view1->getName(), name1);

  EXPECT_EQ(name2, std::string("view2"));
  EXPECT_EQ(view2->getName(), name2);

  // check error conditions
  IndexType idx3 = parent->getViewIndex("view3");
  EXPECT_TRUE(idx3 == InvalidIndex);

  const std::string& name3 = parent->getViewName(idx3);
  EXPECT_TRUE(name3.empty());
  EXPECT_FALSE(nameIsValid(name3));

  delete ds;
}

//------------------------------------------------------------------------------
// Verify getFirstValidViewIndex, getNextValidGroupIndex
//------------------------------------------------------------------------------
TEST(sidre_group,get_first_and_next_view_index)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  DataGroup * parent = root->createGroup("parent");
  DataView * view1 = parent->createView("view1");
  DataView * view2 = parent->createView("view2");

  DataGroup * emptyGroup = root->createGroup("emptyGroup");

  EXPECT_EQ(parent->getNumViews(), 2u);

  IndexType idx1 = parent->getFirstValidViewIndex();
  IndexType idx2 = parent->getNextValidViewIndex(idx1);

  const std::string& name1 = parent->getViewName(idx1);
  const std::string& name2 = parent->getViewName(idx2);

  EXPECT_EQ(name1, std::string("view1"));
  EXPECT_EQ(view1->getName(), name1);

  EXPECT_EQ(name2, std::string("view2"));
  EXPECT_EQ(view2->getName(), name2);

  // check error conditions
  IndexType badidx1 = emptyGroup->getFirstValidViewIndex();
  IndexType badidx2 = emptyGroup->getNextValidViewIndex(badidx1);

  EXPECT_TRUE(badidx1 == InvalidIndex);
  EXPECT_TRUE(badidx2 == InvalidIndex);

  delete ds;
}
//------------------------------------------------------------------------------
// Verify getGroupName(), getGroupIndex()
//------------------------------------------------------------------------------
TEST(sidre_group,get_group_name_index)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();

  DataGroup * parent = root->createGroup("parent");
  DataGroup * group1 = parent->createGroup("group1");
  DataGroup * group2 = parent->createGroup("group2");

  EXPECT_EQ(parent->getNumGroups(), 2u);

  IndexType idx1 = parent->getGroupIndex("group1");
  IndexType idx2 = parent->getGroupIndex("group2");

  const std::string& name1 = parent->getGroupName(idx1);
  const std::string& name2 = parent->getGroupName(idx2);

  EXPECT_EQ(name1, std::string("group1"));
  EXPECT_EQ(group1->getName(), name1);

  EXPECT_EQ(name2, std::string("group2"));
  EXPECT_EQ(group2->getName(), name2);

  // check error conditions
  IndexType idx3 = parent->getGroupIndex("group3");
  EXPECT_TRUE(idx3 == InvalidIndex);

  const std::string& name3 = parent->getGroupName(idx3);
  EXPECT_TRUE(name3.empty());
  EXPECT_FALSE(nameIsValid(name3));

  delete ds;
}

//------------------------------------------------------------------------------
// createView()
// createViewAndAllocate()
// destroyView()
// destroyViewAndData()
// hasView()
//------------------------------------------------------------------------------
TEST(sidre_group,create_destroy_has_view)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  DataGroup * group = root->createGroup("parent");

  DataView * view = group->createView("view");
  EXPECT_TRUE( group->getParent() == root );
  EXPECT_FALSE( view->hasBuffer() );
  EXPECT_TRUE( group->hasView("view") );
  IndexType iview = group->getViewIndex("view");
  EXPECT_EQ(0, iview);

  // try creating view again, should be a no-op.
  EXPECT_TRUE( group->createView("view") == ATK_NULLPTR );

  // Create another view to make sure destroyView only destroys one view
  group->createView("viewfiller");
  EXPECT_EQ(2u, group->getNumViews());
  IndexType iviewfiller = group->getViewIndex("viewfiller");
  EXPECT_EQ(1, iviewfiller);

  group->destroyView("view");
  EXPECT_EQ(1u, group->getNumViews());
  // Check if index changed
  EXPECT_EQ(iviewfiller, group->getViewIndex("viewfiller"));

  // destroy already destroyed group.  Should be a no-op, not a failure
  group->destroyView("view");
  EXPECT_EQ(1u, group->getNumViews());
  EXPECT_FALSE( group->hasView("view") );

  // try api call that specifies specific type and length
  group->createViewAndAllocate( "viewWithLength1",INT_ID, 50 );
  IndexType iview2 = group->getViewIndex("viewWithLength1");
  EXPECT_EQ(iview, iview2);  // reuse slot

  // error condition check - try again with duplicate name, should be a no-op
  EXPECT_TRUE( group->createViewAndAllocate( "viewWithLength1", FLOAT64_ID,
                                             50 ) == ATK_NULLPTR );
  group->destroyViewAndData("viewWithLength1");
  EXPECT_FALSE( group->hasView("viewWithLength1") );

  EXPECT_TRUE( group->createViewAndAllocate( "viewWithLengthBadLen", FLOAT64_ID,
                                             -1 ) == ATK_NULLPTR );

  // try api call that specifies data type in another way
  group->createViewAndAllocate( "viewWithLength2", DataType::float64(50) );
  EXPECT_TRUE( group->createViewAndAllocate( "viewWithLength2",
                                             DataType::float64(
                                               50) ) == ATK_NULLPTR );
  // destroy view and its buffer using index
  IndexType indx = group->getFirstValidViewIndex();
  IndexType bindx = group->getView( indx )->getBuffer()->getIndex();
  group->destroyViewAndData( indx );
  EXPECT_TRUE( ds->getBuffer(bindx) == NULL );

  // Destroy view but not the buffer
  view = group->createViewAndAllocate( "viewWithLength2", INT_ID, 50 );
  DataBuffer * buff = view->getBuffer();
  group->destroyView("viewWithLength2");
  EXPECT_TRUE( buff->isAllocated() );

  delete ds;
}

//------------------------------------------------------------------------------
// createGroup()
// destroyGroup()
// hasGroup()
//------------------------------------------------------------------------------
TEST(sidre_group,create_destroy_has_group)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  DataGroup * group = root->createGroup("group");
  EXPECT_TRUE( group->getParent() == root );

  EXPECT_TRUE( root->hasGroup("group") );

  root->destroyGroup("group");
  EXPECT_FALSE( root->hasGroup("group") );

  // should be a no-op, not a failure
  root->destroyGroup("group");

  DataGroup * group2 = root->createGroup("group2");
  // shut up compiler about unused variable
  (void)group2;
  root->destroyGroup( root->getFirstValidGroupIndex() );

  delete ds;
}

//------------------------------------------------------------------------------
TEST(sidre_group,group_name_collisions)
{
  DataStore * ds = new DataStore();
  DataGroup * flds = ds->getRoot()->createGroup("fields");
  flds->createView("a");

  EXPECT_TRUE(flds->hasView("a"));

  // attempt to create duplicate group name

  DataGroup * badGroup = ds->getRoot()->createGroup("fields");
  EXPECT_TRUE( badGroup == ATK_NULLPTR );

  // check error condition
  // attempt to create duplicate view name.
  EXPECT_TRUE(flds->createView("a") == ATK_NULLPTR);

  delete ds;
}
//------------------------------------------------------------------------------

TEST(sidre_group,view_copy_move)
{
  DataStore * ds = new DataStore();
  DataGroup * flds = ds->getRoot()->createGroup("fields");
  int * buffdata;
  int extdata[10];

  DataView * views[6];
  std::string names[6];

  // Create view in different states
  views[0] = flds->createView("empty0");
  views[1] = flds->createView("empty1", INT_ID, 10);
  views[2] = flds->createViewAndAllocate("buffer", INT_ID, 10);
  views[3] = flds->createView("external", INT_ID, 10)->setExternalDataPtr(
    extdata);
  views[4] = flds->createViewScalar("scalar", 25);
  views[5] = flds->createViewString("string", "I am string");

  buffdata = flds->getView("buffer")->getData();
  for (int i=0 ; i < 10 ; ++i)
  {
    extdata[i] = i;
    buffdata[i] = i + 100;
  }

  for (int i = 0 ; i < 6 ; ++i)
  {
    names[i] = views[i]->getName();
    EXPECT_TRUE(flds->hasView(names[i]));
  }

  // test moving a view from flds to sub1
  DataGroup * sub1 = flds->createGroup("sub1");

  // flds->print();

  for (int i = 0 ; i < 6 ; ++i)
  {
    sub1->moveView(views[i]);
    EXPECT_FALSE(flds->hasView(names[i]));
    EXPECT_TRUE(sub1->hasView(names[i]));

    // moving to same group is a no-op
    sub1->moveView(views[i]);
    EXPECT_TRUE(sub1->hasView(names[i]));
  }

  // flds->print();

  DataGroup * sub2 = flds->createGroup("sub2");

  for (int i = 0 ; i < 6 ; ++i)
  {
    sub2->copyView(views[i]);
    EXPECT_TRUE(sub1->hasView(names[i]));
    EXPECT_TRUE(sub2->hasView(names[i]));
  }

  // Check copies
  DataView * view1 = sub1->getView("empty0");
  DataView * view2 = sub2->getView("empty0");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->isEmpty());
  EXPECT_FALSE(view2->isDescribed());
  EXPECT_FALSE(view2->isAllocated());
  EXPECT_FALSE(view2->isApplied());

  view1 = sub1->getView("empty1");
  view2 = sub2->getView("empty1");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->isEmpty());
  EXPECT_TRUE(view2->isDescribed());
  EXPECT_FALSE(view2->isAllocated());
  EXPECT_FALSE(view2->isApplied());

  view1 = sub1->getView("buffer");
  view2 = sub2->getView("buffer");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->hasBuffer());
  EXPECT_TRUE(view2->isDescribed());
  EXPECT_TRUE(view2->isAllocated());
  EXPECT_TRUE(view2->isApplied());
  EXPECT_TRUE(view1->getBuffer() == view2->getBuffer());
  EXPECT_EQ(2, view1->getBuffer()->getNumViews());

  view1 = sub1->getView("external");
  view2 = sub2->getView("external");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->isExternal());
  EXPECT_TRUE(view2->isDescribed());
  EXPECT_TRUE(view2->isAllocated());
  EXPECT_TRUE(view2->isApplied());
  EXPECT_EQ(view1->getVoidPtr(), view2->getVoidPtr());

  view1 = sub1->getView("scalar");
  view2 = sub2->getView("scalar");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->isScalar());
  EXPECT_TRUE(view2->isDescribed());
  EXPECT_TRUE(view2->isAllocated());
  EXPECT_TRUE(view2->isApplied());
  EXPECT_EQ( view1->getData<int>(), view2->getData<int>());

  view1 = sub1->getView("string");
  view2 = sub2->getView("string");
  EXPECT_NE(view1, view2);
  EXPECT_TRUE(view2->isString());
  EXPECT_TRUE(view2->isDescribed());
  EXPECT_TRUE(view2->isAllocated());
  EXPECT_TRUE(view2->isApplied());
  const char * svalue = view1->getString();
  EXPECT_TRUE(strcmp("I am string", svalue) == 0);

  // flds->print();

  delete ds;
}

//------------------------------------------------------------------------------

TEST(sidre_group,groups_move_copy)
{
  DataStore * ds = new DataStore();
  DataGroup * flds = ds->getRoot()->createGroup("fields");

  DataGroup * ga = flds->createGroup("a");
  DataGroup * gb = flds->createGroup("b");
  DataGroup * gc = flds->createGroup("c");

  ga->createViewAndAllocate("i0", DataType::c_int());
  gb->createViewAndAllocate("f0", DataType::c_float());
  gc->createViewAndAllocate("d0", DataType::c_double());

  ga->getView("i0")->setScalar(1);
  gb->getView("f0")->setScalar(100.0);
  gc->getView("d0")->setScalar(3000.0);

  // check that all sub groups exist
  EXPECT_TRUE(flds->hasGroup("a"));
  EXPECT_TRUE(flds->hasGroup("b"));
  EXPECT_TRUE(flds->hasGroup("c"));

  // move "b" to a child of "sub"
  flds->createGroup("sub")->moveGroup(gb);

  // flds->print();

  EXPECT_TRUE(flds->hasGroup("a"));
  EXPECT_TRUE(flds->hasGroup("sub"));
  EXPECT_TRUE(flds->hasGroup("c"));

  EXPECT_EQ(flds->getGroup("sub")->getGroup("b"),gb);

  delete ds;
}

//------------------------------------------------------------------------------
TEST(sidre_group,create_destroy_view_and_buffer2)
{
  DataStore * const ds = new DataStore();
  DataGroup * const grp = ds->getRoot()->createGroup("grp");

  std::string viewName1("viewBuffer1");
  std::string viewName2("viewBuffer2");

  DataView * view1 = grp->createViewAndAllocate(viewName1,
                                                asctoolkit::sidre::INT_ID, 1);
  DataView * view2 = grp->createViewAndAllocate(viewName2,
                                                asctoolkit::sidre::INT_ID, 1);

  EXPECT_TRUE(grp->hasView(viewName1));
  EXPECT_EQ( grp->getView(viewName1), view1 );

  EXPECT_TRUE(grp->hasView(viewName2));
  EXPECT_EQ( grp->getView(viewName2), view2 );

  IndexType const bufferId1 = view1->getBuffer()->getIndex();

  grp->destroyViewAndData(viewName1);

  EXPECT_FALSE(grp->hasView(viewName1));
  EXPECT_EQ(ds->getNumBuffers(), 1u);

  DataBuffer const * const buffer1 = ds->getBuffer(bufferId1);
  EXPECT_TRUE( buffer1 == ATK_NULLPTR );

  DataView const * const view3 = grp->createView("viewBuffer3");
  grp->destroyViewsAndData();
  // should be no-op
  grp->destroyViewsAndData();
  // shut up compiler about unused variable
  (void)view3;

  delete ds;
}


//------------------------------------------------------------------------------
TEST(sidre_group,create_destroy_alloc_view_and_buffer)
{
  DataStore * const ds = new DataStore();
  DataGroup * const grp = ds->getRoot()->createGroup("grp");

  std::string const viewName1 = "viewBuffer1";
  std::string const viewName2 = "viewBuffer2";

  // use create + alloc convenience methods
  // this one is the DataType & method
  DataView * const view1 = grp->createViewAndAllocate(viewName1,
                                                      DataType::c_int(10));

  EXPECT_TRUE(grp->hasView(viewName1));
  EXPECT_EQ( grp->getView(viewName1), view1 );

  int * v1_vals = view1->getData();

  for(int i=0 ; i<10 ; i++)
  {
    v1_vals[i] = i;
  }

  EXPECT_EQ(view1->getNumElements(), 10u);
  EXPECT_EQ(view1->getTotalBytes(),
            static_cast<asctoolkit::sidre::SidreLength>(10 * sizeof(int)));

  grp->destroyViewAndData(viewName1);

  delete ds;
}

//------------------------------------------------------------------------------
TEST(sidre_group,create_view_of_buffer_with_schema)
{
  DataStore * ds = new DataStore();
  DataGroup * root = ds->getRoot();
  // use create + alloc convenience methods
  // this one is the DataType & method
  DataView * base =  root->createViewAndAllocate("base", DataType::c_int(10));
  int * base_vals = base->getData();
  for(int i=0 ; i<10 ; i++)
  {
    if(i < 5)
    {
      base_vals[i] = 10;
    }
    else
    {
      base_vals[i] = 20;
    }
  }

  DataBuffer * base_buff = base->getBuffer();

  // create two views into this buffer
  //
  // view for the first 5 values
  root->createView("sub_a", base_buff)->apply(DataType::c_int(5));

  int * sub_a_vals = root->getView("sub_a")->getData();

  for(int i=0 ; i<5 ; i++)
  {
    EXPECT_EQ(sub_a_vals[i], 10);
  }

  delete ds;
}

//------------------------------------------------------------------------------
TEST(sidre_group,save_restore_empty)
{
  DataStore * ds = new DataStore();

  ds->save("sidre_empty_datastore", "conduit");

  delete ds;

  ds = new DataStore();
  ds->load("sidre_empty_datastore", "conduit");

  EXPECT_TRUE(ds->getNumBuffers() == 0 );
  EXPECT_TRUE(ds->getRoot()->getNumGroups() == 0 );
  EXPECT_TRUE(ds->getRoot()->getNumViews() == 0 );

}

//------------------------------------------------------------------------------
TEST(sidre_group,save_restore_api)
{
  DataStore * ds1 = new DataStore();

  ds1->getRoot()->createViewScalar<int>("i0", 1);

  // These should be produce identical files.

  // No group provided, defaults to root group
  ds1->save("sidre_save_fulltree", "conduit");
  // Pass in group (example of saving sub-tree).
  ds1->save("sidre_save_subtree", "conduit", ds1->getRoot());

  // Text output ( for debugging ).  Write support only ( no load ).
  ds1->save("sidre_save_textoutput", "text", ds1->getRoot());

  // HDF5 output
  ds1->save("sidre_save_conduithdf5","conduit_hdf5");

  DataStore * ds2 = new DataStore();
  DataStore * ds3 = new DataStore();
  DataStore * ds4 = new DataStore();

  ds2->load("sidre_save_fulltree", "conduit");
  ds3->load("sidre_save_subtree", "conduit", ds3->getRoot() );
  ds4->load("sidre_save_conduithdf5", "conduit_hdf5");

  EXPECT_TRUE( ds2->getRoot()->isEquivalentTo(ds1->getRoot()) );
  EXPECT_TRUE( ds3->getRoot()->isEquivalentTo(ds1->getRoot()) );
  EXPECT_TRUE( ds4->getRoot()->isEquivalentTo(ds1->getRoot()) );

  delete ds1;
  delete ds2;
  delete ds3;
  delete ds4;

  // Why don't these pass??? Need to ask Noah about this...
  // Trying to make sure sub trees are same here.
#if 0
  DataStore * ds_new = new DataStore();
  DataGroup * tree1 = ds_new->getRoot()->createGroup("api1");
  DataGroup * tree2 = ds_new->getRoot()->createGroup("api2");

  api1->load("sidre_save_subtree", "conduit");
  api2->load("sidre_save_subtree", "conduit");

  EXPECT_TRUE( api1->isEquivalentTo( api2) );
#endif

}

//------------------------------------------------------------------------------
TEST(sidre_group,save_restore_scalars_and_strings)
{
  DataStore * ds1 = new DataStore();

  ds1->getRoot()->createViewScalar<int>("i0", 1);
  ds1->getRoot()->createViewScalar<float>("f0", 1.0);
  ds1->getRoot()->createViewScalar<double>("d0", 10.0);

  ds1->save("sidre_save_scalars_and_strings", "conduit");

  DataStore * ds2 = new DataStore();

  ds2->load("sidre_save_scalars_and_strings", "conduit");

  EXPECT_TRUE( ds1->getRoot()->isEquivalentTo( ds2->getRoot()) );

  delete ds1;
  delete ds2;
}

//------------------------------------------------------------------------------
TEST(sidre_group,save_restore_external_data)
{
  int foo[100];
  for (int i =0; i < 100; ++i)
  {
    foo[i] = i;
  }

  DataStore * ds = new DataStore();

  DataView * view = ds->getRoot()->createView("external_array", &foo[0] );
  view->apply( asctoolkit::sidre::INT_ID, 100 );

  ds->save("sidre_save_external", "conduit");

  delete ds;

  // Now load back in.
  ds = new DataStore();
  ds->load("sidre_save_external", "conduit");

  // All this code should change after we re-write how we handle restoring external data.
  // Right now, the external data is coming back in the view's node and we have to do extra work to
  // restore it to the user's pointer.
  view = ds->getRoot()->getView("external_array");

  int* new_data_pointer = new int[100];

  EXPECT_TRUE( view->getTotalBytes() == sizeof( int[100] ) );

  std::memcpy(&new_data_pointer[0], view->getVoidPtr(), view->getTotalBytes() );

  // Will set view back to EMPTY and reset node.  Will leave description alone.
  view->setExternalDataPtr( ATK_NULLPTR );

  view->setExternalDataPtr( new_data_pointer );

  for (int i = 0; i < 100; ++i)
  {
    EXPECT_TRUE( static_cast<int*>( view->getVoidPtr() )[i] == i );
  }

  delete[] new_data_pointer;
  delete ds;
}

//------------------------------------------------------------------------------
TEST(sidre_group,save_restore_complex)
{
  DataStore * ds = new DataStore();
  DataGroup * flds = ds->getRoot()->createGroup("fields");

  DataGroup * ga = flds->createGroup("a");
  DataGroup * gb = flds->createGroup("b");
  DataGroup * gc = flds->createGroup("c");

  ga->createViewScalar<int>("i0", 100.0);
  ga->createViewScalar<double>("d0", 3000.00);
  gb->createViewString("s0", "foo");

  gc->createViewAndAllocate("int100", asctoolkit::sidre::INT_ID, 100);
  int* data_ptr = gc->getView("int100")->getArray();
  for (int i =0; i < 100; ++i)
  {
    data_ptr[i] = i;
  }

  ds->save("sidre_mixed_types","conduit");

  DataStore * ds2 = new DataStore();

  ds2->load("sidre_mixed_types","conduit");

  EXPECT_TRUE( ds->getRoot()->isEquivalentTo(ds2->getRoot()) );

  delete ds;

  flds = ds2->getRoot()->getGroup("fields");

  // check that all sub groups exist
  EXPECT_TRUE(flds->hasGroup("a"));
  EXPECT_TRUE(flds->hasGroup("b"));
  EXPECT_TRUE(flds->hasGroup("c"));

  EXPECT_EQ(flds->getGroup("a")->getView("i0")->getData<int>(),100.0);
  EXPECT_NEAR(flds->getGroup("a")->getView("d0")->getData<double>(),3000.0, 1e-12);

  int* new_data_ptr = flds->getGroup("c")->getView("int100")->getArray();
  for (int i = 0; i < 100; ++i)
  {
    EXPECT_TRUE( new_data_ptr[i] == i);
  }

  // TODO - Figure out the right way to get the string value our of conduit node!!
  //char * char_ptr = flds->getGroup("b")->getView("s0")->getString();
  //EXPECT_TRUE( std::string(char_ptr) == "foo" );



  //ds2->print();

  delete ds2;
  }

//------------------------------------------------------------------------------
// isEquivalentTo()
//------------------------------------------------------------------------------
TEST(sidre_group,is_equivalent_to)
{
  DataStore * ds = new DataStore();

  //These are the parents for two separate subtrees of the root group.
  //Everything below them will be created identically.
  DataGroup * parent1 = ds->getRoot()->createGroup("parent1");
  DataGroup * parent2 = ds->getRoot()->createGroup("parent2");

  //The flds1 and flds2 groups will be compared for equivalence
  DataGroup * flds1 = parent1->createGroup("fields");
  DataGroup * flds2 = parent2->createGroup("fields");

  DataGroup * ga1 = flds1->createGroup("a");
  DataGroup * gb1 = flds1->createGroup("b");
  DataGroup * gc1 = flds1->createGroup("c");
  DataGroup * ga2 = flds2->createGroup("a");
  DataGroup * gb2 = flds2->createGroup("b");
  DataGroup * gc2 = flds2->createGroup("c");

  ga1->createViewScalar("i0", 1 );
  gb1->createViewScalar("f0", 100.0f );
  gc1->createViewScalar("d0", 3000.00);
  ga2->createViewScalar("i0", 1);
  gb2->createViewScalar("f0", 100.0f);
  gc2->createViewScalar("d0", 3000.00);

  ga1->getView("i0")->setScalar(1);
  gb1->getView("f0")->setScalar( 100.0f );
  gc1->getView("d0")->setScalar(3000.00);
  ga2->getView("i0")->setScalar(1);
  gb2->getView("f0")->setScalar( 100.0f );
  gc2->getView("d0")->setScalar(3000.00);

  // Groups were created identically, so should be equivalent.
  EXPECT_TRUE(flds1->isEquivalentTo(flds2));

  // Add something extra to flds2, making them not equivalent.
  gc2->createViewAndAllocate("extra", DataType::c_double());

  EXPECT_FALSE(flds1->isEquivalentTo(flds2));

  delete ds;

}