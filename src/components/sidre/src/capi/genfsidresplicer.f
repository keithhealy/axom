! Generated by genfsidresplicer.py
! splicer begin class.DataStore.module_top
interface c_loc_allocatable

   function atk_c_loc_allocatable_int_scalar(variable) result(rv)
     use iso_c_binding
     integer(C_INT), allocatable, intent(IN) :: variable
     type(C_PTR) rv
   end function atk_c_loc_allocatable_int_scalar

   function atk_c_loc_allocatable_int_1d(variable) result(rv)
     use iso_c_binding
     integer(C_INT), allocatable, intent(IN) :: variable(:)
     type(C_PTR) rv
   end function atk_c_loc_allocatable_int_1d

   function atk_c_loc_allocatable_long_scalar(variable) result(rv)
     use iso_c_binding
     integer(C_LONG), allocatable, intent(IN) :: variable
     type(C_PTR) rv
   end function atk_c_loc_allocatable_long_scalar

   function atk_c_loc_allocatable_long_1d(variable) result(rv)
     use iso_c_binding
     integer(C_LONG), allocatable, intent(IN) :: variable(:)
     type(C_PTR) rv
   end function atk_c_loc_allocatable_long_1d

   function atk_c_loc_allocatable_float_scalar(variable) result(rv)
     use iso_c_binding
     real(C_FLOAT), allocatable, intent(IN) :: variable
     type(C_PTR) rv
   end function atk_c_loc_allocatable_float_scalar

   function atk_c_loc_allocatable_float_1d(variable) result(rv)
     use iso_c_binding
     real(C_FLOAT), allocatable, intent(IN) :: variable(:)
     type(C_PTR) rv
   end function atk_c_loc_allocatable_float_1d

   function atk_c_loc_allocatable_double_scalar(variable) result(rv)
     use iso_c_binding
     real(C_DOUBLE), allocatable, intent(IN) :: variable
     type(C_PTR) rv
   end function atk_c_loc_allocatable_double_scalar

   function atk_c_loc_allocatable_double_1d(variable) result(rv)
     use iso_c_binding
     real(C_DOUBLE), allocatable, intent(IN) :: variable(:)
     type(C_PTR) rv
   end function atk_c_loc_allocatable_double_1d
end interface c_loc_allocatable
! splicer end class.DataStore.module_top

! splicer begin class.DataGroup.type_bound_procedure_part
procedure :: create_allocatable_view_int_scalar => datagroup_create_allocatable_view_int_scalar
procedure :: create_allocatable_view_int_1d => datagroup_create_allocatable_view_int_1d
procedure :: create_allocatable_view_long_scalar => datagroup_create_allocatable_view_long_scalar
procedure :: create_allocatable_view_long_1d => datagroup_create_allocatable_view_long_1d
procedure :: create_allocatable_view_float_scalar => datagroup_create_allocatable_view_float_scalar
procedure :: create_allocatable_view_float_1d => datagroup_create_allocatable_view_float_1d
procedure :: create_allocatable_view_double_scalar => datagroup_create_allocatable_view_double_scalar
procedure :: create_allocatable_view_double_1d => datagroup_create_allocatable_view_double_1d
generic :: create_allocatable_view => &
    create_allocatable_view_int_scalar,  &
    create_allocatable_view_int_1d,  &
    create_allocatable_view_long_scalar,  &
    create_allocatable_view_long_1d,  &
    create_allocatable_view_float_scalar,  &
    create_allocatable_view_float_1d,  &
    create_allocatable_view_double_scalar,  &
    create_allocatable_view_double_1d
procedure :: register_static_int_scalar => datagroup_register_static_int_scalar
procedure :: register_static_int_1d => datagroup_register_static_int_1d
procedure :: register_static_long_scalar => datagroup_register_static_long_scalar
procedure :: register_static_long_1d => datagroup_register_static_long_1d
procedure :: register_static_float_scalar => datagroup_register_static_float_scalar
procedure :: register_static_float_1d => datagroup_register_static_float_1d
procedure :: register_static_double_scalar => datagroup_register_static_double_scalar
procedure :: register_static_double_1d => datagroup_register_static_double_1d
generic :: register_static => &
    register_static_int_scalar,  &
    register_static_int_1d,  &
    register_static_long_scalar,  &
    register_static_long_1d,  &
    register_static_float_scalar,  &
    register_static_float_1d,  &
    register_static_double_scalar,  &
    register_static_double_1d
! splicer end class.DataGroup.type_bound_procedure_part

------------------------------------------------------------

! splicer begin class.DataGroup.additional_functions

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_int_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_int_scalar(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       integer(C_INT), allocatable, intent(IN) :: array
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_int_scalar
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_INT), allocatable, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 0
    integer(C_INT), parameter :: itype = ATK_C_INT_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_int_scalar(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_int_scalar

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_int_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_int_1d(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       integer(C_INT), allocatable, intent(IN) :: array(:)
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_int_1d
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_INT), allocatable, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 1
    integer(C_INT), parameter :: itype = ATK_C_INT_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_int_1d(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_int_1d

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_long_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_long_scalar(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       integer(C_LONG), allocatable, intent(IN) :: array
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_long_scalar
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_LONG), allocatable, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 0
    integer(C_INT), parameter :: itype = ATK_C_LONG_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_long_scalar(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_long_scalar

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_long_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_long_1d(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       integer(C_LONG), allocatable, intent(IN) :: array(:)
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_long_1d
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_LONG), allocatable, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 1
    integer(C_INT), parameter :: itype = ATK_C_LONG_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_long_1d(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_long_1d

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_float_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_float_scalar(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       real(C_FLOAT), allocatable, intent(IN) :: array
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_float_scalar
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_FLOAT), allocatable, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 0
    integer(C_INT), parameter :: itype = ATK_C_FLOAT_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_float_scalar(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_float_scalar

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_float_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_float_1d(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       real(C_FLOAT), allocatable, intent(IN) :: array(:)
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_float_1d
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_FLOAT), allocatable, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 1
    integer(C_INT), parameter :: itype = ATK_C_FLOAT_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_float_1d(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_float_1d

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_double_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_double_scalar(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       real(C_DOUBLE), allocatable, intent(IN) :: array
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_double_scalar
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_DOUBLE), allocatable, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 0
    integer(C_INT), parameter :: itype = ATK_C_DOUBLE_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_double_scalar(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_double_scalar

! Generated by genfsidresplicer.py
function datagroup_create_allocatable_view_double_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_create_allocatable_view_double_1d(group, name, lname, array, itype, rank) &
          result(rv)
       use iso_c_binding
       type(C_PTR), value, intent(IN)    :: group
       character(*), intent(IN)          :: name
       integer(C_INT), value, intent(IN) :: lname
       real(C_DOUBLE), allocatable, intent(IN) :: array(:)
       integer(C_INT), value, intent(IN) :: itype
       integer(C_INT), value, intent(IN) :: rank
       type(C_PTR) rv
       end function ATK_create_allocatable_view_double_1d
    end interface

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_DOUBLE), allocatable, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_INT), parameter :: rank = 1
    integer(C_INT), parameter :: itype = ATK_C_DOUBLE_T

    lname = len_trim(name)
    rv%voidptr = ATK_create_allocatable_view_double_1d(group%voidptr, name, lname, value, itype, rank)
end function datagroup_create_allocatable_view_double_1d

! Generated by genfsidresplicer.py
function datagroup_register_static_int_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_INT), target, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_INT_T

    lname = len_trim(name)
    nitems = 1_C_LONG
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_int_scalar

! Generated by genfsidresplicer.py
function datagroup_register_static_int_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_INT), target, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_INT_T

    lname = len_trim(name)
    nitems = size(value, kind=1_C_LONG)
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_int_1d

! Generated by genfsidresplicer.py
function datagroup_register_static_long_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_LONG), target, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_LONG_T

    lname = len_trim(name)
    nitems = 1_C_LONG
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_long_scalar

! Generated by genfsidresplicer.py
function datagroup_register_static_long_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    integer(C_LONG), target, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_LONG_T

    lname = len_trim(name)
    nitems = size(value, kind=1_C_LONG)
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_long_1d

! Generated by genfsidresplicer.py
function datagroup_register_static_float_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_FLOAT), target, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_FLOAT_T

    lname = len_trim(name)
    nitems = 1_C_LONG
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_float_scalar

! Generated by genfsidresplicer.py
function datagroup_register_static_float_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_FLOAT), target, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_FLOAT_T

    lname = len_trim(name)
    nitems = size(value, kind=1_C_LONG)
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_float_1d

! Generated by genfsidresplicer.py
function datagroup_register_static_double_scalar(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_DOUBLE), target, intent(IN) :: value
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_DOUBLE_T

    lname = len_trim(name)
    nitems = 1_C_LONG
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_double_scalar

! Generated by genfsidresplicer.py
function datagroup_register_static_double_1d(group, name, value) result(rv)
    use iso_c_binding
    implicit none

    interface
       function ATK_register_static(group, name, lname, addr, type, nitems) result(rv) bind(C,name="ATK_register_static")
       use iso_c_binding
       type(C_PTR), value, intent(IN)     :: group
       character(kind=C_CHAR), intent(IN) :: name(*)
       integer(C_INT), value, intent(IN)  :: lname
       type(C_PTR), value,     intent(IN) :: addr
       integer(C_INT), value, intent(IN)  :: type
       integer(C_LONG), value, intent(IN) :: nitems
       type(C_PTR) rv
       end function ATK_register_static
    end interface
    type(C_PTR), external :: ATK_C_LOC

    class(datagroup), intent(IN) :: group
    character(*), intent(IN) :: name
    real(C_DOUBLE), target, intent(IN) :: value(:)
    integer(C_INT) :: lname
    type(dataview) :: rv
    integer(C_LONG) :: nitems
    integer(C_INT) :: type = ATK_C_DOUBLE_T

    lname = len_trim(name)
    nitems = size(value, kind=1_C_LONG)
    rv%voidptr = ATK_register_static(group%voidptr, name, lname, ATK_C_LOC(value), type, nitems)
end function datagroup_register_static_double_1d
! splicer end class.DataGroup.additional_functions
! splicer begin class.DataView.type_bound_procedure_part
procedure :: get_value_int_scalar_ptr => dataview_get_value_int_scalar_ptr
procedure :: get_value_int_1d_ptr => dataview_get_value_int_1d_ptr
procedure :: get_value_long_scalar_ptr => dataview_get_value_long_scalar_ptr
procedure :: get_value_long_1d_ptr => dataview_get_value_long_1d_ptr
procedure :: get_value_float_scalar_ptr => dataview_get_value_float_scalar_ptr
procedure :: get_value_float_1d_ptr => dataview_get_value_float_1d_ptr
procedure :: get_value_double_scalar_ptr => dataview_get_value_double_scalar_ptr
procedure :: get_value_double_1d_ptr => dataview_get_value_double_1d_ptr
generic :: get_value => &
    get_value_int_scalar_ptr,  &
    get_value_int_1d_ptr,  &
    get_value_long_scalar_ptr,  &
    get_value_long_1d_ptr,  &
    get_value_float_scalar_ptr,  &
    get_value_float_1d_ptr,  &
    get_value_double_scalar_ptr,  &
    get_value_double_1d_ptr
! splicer end class.DataView.type_bound_procedure_part

------------------------------------------------------------

! splicer begin class.DataView.additional_functions

! Generated by genfsidresplicer.py
subroutine dataview_get_value_int_scalar_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    integer(C_INT), pointer, intent(OUT) :: value
    type(C_PTR) cptr

    cptr = view%get_data_pointer()
    call c_f_pointer(cptr, value)
end subroutine dataview_get_value_int_scalar_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_int_1d_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    integer(C_INT), pointer, intent(OUT) :: value(:)
    type(C_PTR) cptr
    integer(C_SIZE_T) nelems

    cptr = view%get_data_pointer()
    nelems = view%get_number_of_elements()
    call c_f_pointer(cptr, value, [ nelems ])
end subroutine dataview_get_value_int_1d_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_long_scalar_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    integer(C_LONG), pointer, intent(OUT) :: value
    type(C_PTR) cptr

    cptr = view%get_data_pointer()
    call c_f_pointer(cptr, value)
end subroutine dataview_get_value_long_scalar_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_long_1d_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    integer(C_LONG), pointer, intent(OUT) :: value(:)
    type(C_PTR) cptr
    integer(C_SIZE_T) nelems

    cptr = view%get_data_pointer()
    nelems = view%get_number_of_elements()
    call c_f_pointer(cptr, value, [ nelems ])
end subroutine dataview_get_value_long_1d_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_float_scalar_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    real(C_FLOAT), pointer, intent(OUT) :: value
    type(C_PTR) cptr

    cptr = view%get_data_pointer()
    call c_f_pointer(cptr, value)
end subroutine dataview_get_value_float_scalar_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_float_1d_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    real(C_FLOAT), pointer, intent(OUT) :: value(:)
    type(C_PTR) cptr
    integer(C_SIZE_T) nelems

    cptr = view%get_data_pointer()
    nelems = view%get_number_of_elements()
    call c_f_pointer(cptr, value, [ nelems ])
end subroutine dataview_get_value_float_1d_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_double_scalar_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    real(C_DOUBLE), pointer, intent(OUT) :: value
    type(C_PTR) cptr

    cptr = view%get_data_pointer()
    call c_f_pointer(cptr, value)
end subroutine dataview_get_value_double_scalar_ptr

! Generated by genfsidresplicer.py
subroutine dataview_get_value_double_1d_ptr(view, value)
    use iso_c_binding
    implicit none
    class(dataview), intent(IN) :: view
    real(C_DOUBLE), pointer, intent(OUT) :: value(:)
    type(C_PTR) cptr
    integer(C_SIZE_T) nelems

    cptr = view%get_data_pointer()
    nelems = view%get_number_of_elements()
    call c_f_pointer(cptr, value, [ nelems ])
end subroutine dataview_get_value_double_1d_ptr
! splicer end class.DataView.additional_functions
