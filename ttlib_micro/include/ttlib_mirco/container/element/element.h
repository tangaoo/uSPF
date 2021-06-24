/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       element.h
 * @ingroup    container
 * @author     tango
 * @date       2020-11-19 
 * @brief      element.h file
 */

#ifndef TT_CONTAINER_ELEMENT_ELEMENT_H
#define TT_CONTAINER_ELEMENT_ELEMENT_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
/// the element ref type
typedef struct __tt_element_t *   tt_element_ref_t;

/*! the element data hash function type
 *
 * @param e                     the element
 * @param data                  the element data
 * @param mask                  the hash mask
 * @param index                 the hash index
 *
 * @return                      the hash value
 */
typedef tt_size_t               (*tt_element_hash_func_t)(tt_element_ref_t e, tt_cpointer_t data, tt_size_t mask, tt_size_t index);

/*! the element data compare function type
 *
 * @param element               the element
 * @param ldata                 the left-hand data
 * @param rdata                 the right-hand data
 *
 * @return                      equal: 0, 1: >, -1: <
 */
typedef tt_long_t               (*tt_element_comp_func_t)(tt_element_ref_t e, tt_cpointer_t ldata, tt_cpointer_t rdata);

/*! the element data function type
 *
 * @param element               the element
 * @param buff                  the element data address
 *
 * @return                      the element data
 */
typedef tt_pointer_t            (*tt_element_data_func_t)(tt_element_ref_t e, tt_cpointer_t buff);

/*! the element data string function type
 *
 * @param element               the element
 * @param data                  the element data
 * @param str                   the string buffer
 * @param maxn                  the string buffer maximum size
 *
 * @return                      the string pointer
 */
typedef tt_char_t const *       (*tt_element_cstr_func_t)(tt_element_ref_t e, tt_cpointer_t data, tt_char_t *str, tt_size_t maxn);

/*! the element free function type
 *
 * @param element               the element
 * @param buff                  the element buffer
 */
typedef tt_void_t               (*tt_element_free_func_t)(tt_element_ref_t e, tt_pointer_t buff);

/*! the element duplicate function type
 *
 * allocate a new element and copy the element data
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 */
typedef tt_void_t               (*tt_element_dupl_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data);

/*! the element replace function type
 *
 * free the previous element data and duplicate the new data
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 */
typedef tt_void_t               (*tt_element_repl_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data);

/*! the element copy function type
 *
 * only copy the element data and not allocate new element
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 */
typedef tt_void_t               (*tt_element_copy_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data);

/*! the elements free function type
 *
 * free some elements
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param size                  the element count
 */
typedef tt_void_t               (*tt_element_nfree_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_size_t size);

/*! the elements duplicate function type
 *
 * duplicate some elements
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 * @param size                  the element count
 */
typedef tt_void_t               (*tt_element_ndupl_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size);

/*! the elements replace function type
 *
 * replace some elements
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 * @param size                  the element count
 */
typedef tt_void_t               (*tt_element_nrepl_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size);

/*! the elements copy function type
 *
 * copy some elements
 *
 * @param element               the element
 * @param buff                  the element buffer
 * @param data                  the element data
 * @param size                  the element count
 */
typedef tt_void_t               (*tt_element_ncopy_func_t)(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size);


/// the element type
typedef enum __tt_element_type_e
{
    TT_ELEMENT_TYPE_NULL           = 0     //!< null
,   TT_ELEMENT_TYPE_LONG           = 1     //!< long 
,   TT_ELEMENT_TYPE_SIZE           = 2     //!< size 
,   TT_ELEMENT_TYPE_UINT8          = 3     //!< uint8
,   TT_ELEMENT_TYPE_UINT16         = 4     //!< uint16
,   TT_ELEMENT_TYPE_UINT32         = 5     //!< uint32
,   TT_ELEMENT_TYPE_STR            = 6     //!< string
,   TT_ELEMENT_TYPE_PTR            = 7     //!< pointer
,   TT_ELEMENT_TYPE_MEM            = 8     //!< memory
,   TT_ELEMENT_TYPE_OBJ            = 9     //!< object
,   TT_ELEMENT_TYPE_TRUE           = 10    //!< true
,   TT_ELEMENT_TYPE_USER           = 11    //!< the user-defined type    

}tt_element_type_e;

/// the element type
typedef struct __tt_element_t
{
    /// the element type
    tt_uint16_t                           type;

    /// the element flag
    tt_uint16_t                           flag;

    /// the element size
    tt_uint16_t                           size;

    /// the priv data
    tt_cpointer_t                         priv;

    /// the hash function
    tt_element_hash_func_t                hash;

    /// the commpare function
    tt_element_comp_func_t                comp;

    /// the data function
    tt_element_data_func_t                data;

    /// the string function
    tt_element_cstr_func_t                cstr;

    /// the free function
    tt_element_free_func_t                free;

    /// the duplicate function
    tt_element_dupl_func_t                dupl;

    /// the replace function
    tt_element_repl_func_t                repl;

    /// the copy functoin
    tt_element_copy_func_t                copy;

    /// the free elements function
    tt_element_nfree_func_t               nfree;

    /// the duplicate elements function
    tt_element_ndupl_func_t               ndupl;

    /// the replace elements function
    tt_element_nrepl_func_t               nrepl;    

    /// the copy elements functoin
    tt_element_ncopy_func_t               ncopy;

}tt_element_t;


/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! the uint8 element
 *
 * @return          the element
 */
tt_element_t        tt_element_uint8(tt_noarg_t);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif
