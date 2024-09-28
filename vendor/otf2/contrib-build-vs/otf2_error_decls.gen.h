    UTILS_ERROR_DECL( END_OF_FUNCTION, "Unintentional reached end of function"),
    UTILS_ERROR_DECL( INVALID_CALL, "Function call not allowed in current state"),
    UTILS_ERROR_DECL( INVALID_ARGUMENT, "Parameter value out of range"),
    UTILS_ERROR_DECL( INVALID_RECORD, "Invalid definition or event record"),
    UTILS_ERROR_DECL( INVALID_DATA, "Invalid or inconsistent record data"),
    UTILS_ERROR_DECL( INVALID_SIZE_GIVEN, "The given size cannot be used"),
    UTILS_ERROR_DECL( UNKNOWN_TYPE, "The given type is not known"),
    UTILS_ERROR_DECL( INTEGRITY_FAULT, "The structural integrity is not given"),
    UTILS_ERROR_DECL( MEM_FAULT, "This could not be done with the given memory"),
    UTILS_ERROR_DECL( MEM_ALLOC_FAILED, "Memory allocation failed"),
    UTILS_ERROR_DECL( PROCESSED_WITH_FAULTS, "An error appeared when data was processed"),
    UTILS_ERROR_DECL( INDEX_OUT_OF_BOUNDS, "Index out of bounds"),
    UTILS_ERROR_DECL( INVALID_LINENO, "Invalid source code line number"),
    UTILS_ERROR_DECL( END_OF_BUFFER, "End of buffer/file reached"),
    UTILS_ERROR_DECL( FILE_INTERACTION, "Invalid file operation"),
    UTILS_ERROR_DECL( FILE_CAN_NOT_OPEN, "Unable to open file"),
    UTILS_ERROR_DECL( INTERRUPTED_BY_CALLBACK, "Record reading interrupted by reader callback"),
    UTILS_ERROR_DECL( PROPERTY_NAME_INVALID, "Property name does not conform to the naming scheme"),
    UTILS_ERROR_DECL( PROPERTY_EXISTS, "Property already exists"),
    UTILS_ERROR_DECL( PROPERTY_NOT_FOUND, "Property not found found in this archive"),
    UTILS_ERROR_DECL( PROPERTY_VALUE_INVALID, "Property value does not have the expected value"),
    UTILS_ERROR_DECL( FILE_COMPRESSION_NOT_SUPPORTED, "Missing library support for requested compression mode"),
    UTILS_ERROR_DECL( DUPLICATE_MAPPING_TABLE, "Multiple definitions for the same mapping type"),
    UTILS_ERROR_DECL( INVALID_FILE_MODE_TRANSITION, "File mode transition not permitted"),
    UTILS_ERROR_DECL( COLLECTIVE_CALLBACK, "Collective callback failed"),
    UTILS_ERROR_DECL( FILE_SUBSTRATE_NOT_SUPPORTED, "Missing library support for requested file substrate"),
    UTILS_ERROR_DECL( INVALID_ATTRIBUTE_TYPE, "The type of the attribute does not match the expected one."),
    UTILS_ERROR_DECL( LOCKING_CALLBACK, "Locking callback failed"),
    UTILS_ERROR_DECL( HINT_INVALID, "The hint is not valid for the current operation mode of OTF2."),
    UTILS_ERROR_DECL( HINT_LOCKED, "The hint was either already set by the user or at least once queried from OTF2."),
    UTILS_ERROR_DECL( HINT_INVALID_VALUE, "Invalid value for hint."),
