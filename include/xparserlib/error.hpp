#ifndef XPARSERLIB_ERROR_HPP
#define XPARSERLIB_ERROR_HPP


#include "string_type.hpp"


namespace xparserlib {


    /**
     * The error type.
     */
    using error_type = int;


    /**
     * A error.
     */
    class error {
    public:
        /**
         * The default constructor.
         */
        error() {}

        /**
         * The constructor.
         * @param type type of error.
         * @param position the error position.
         */
        error(error_type type, const iterator_type& position);

        /**
         * Returns the type of error.
         * @return the type of error.
         */
        error_type type() const;

        /**
         * Returns the error position in the source string.
         * @return the error position in the source string.
         */
        const iterator_type& position() const;

    private:
        error_type m_type;
        iterator_type m_position;
    };


    /**
     * Container of errors.
     */
    using errors_type = std::vector<class error>;


} //namespace xparserlib


#endif //XPARSERLIB_ERROR_HPP
