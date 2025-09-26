#ifndef XPARSERLIB_ERROR_HPP
#define XPARSERLIB_ERROR_HPP


#include "string_type.hpp"


namespace xparserlib {


    /**
     * The error type.
     */
    using error_type = int;


    class tapm;
    class parse_context;


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
         * @param begin the error begin position.
         * @param end the error end position.
         */
        error(error_type type, const iterator_type& begin, const iterator_type& end);

        /**
         * Returns the type of error.
         * @return the type of error.
         */
        error_type type() const;

        /**
         * Returns the error begin position in the source string.
         * @return the error begin position in the source string.
         */
        const iterator_type& begin() const;

        /**
         * Returns the error end position in the source string.
         * @return the error end position in the source string.
         */
        const iterator_type& end() const;

    private:
        error_type m_type;
        iterator_type m_begin;
        iterator_type m_end;

        friend class tapm;
        friend class parse_context;
    };


    /**
     * Container of errors.
     */
    using errors_type = std::vector<class error>;


} //namespace xparserlib


#endif //XPARSERLIB_ERROR_HPP
