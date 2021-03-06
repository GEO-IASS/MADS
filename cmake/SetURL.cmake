#  -*- mode: cmake -*-
function(SetURL PACKAGE ARCHIVE_FILE URL )
if( EXISTS ${TPL_REPO_DIR}/${ARCHIVE_FILE} )
    message(STATUS "${PACKAGE} is available in the TPL's repository for MADS (${TPL_REPO_DIR}/${ARCHIVE_FILE})" )
    set(${URL} ${TPL_REPO_DIR}/${ARCHIVE_FILE} PARENT_SCOPE)
elseif( EXISTS ${TPL_DOWNLOAD_DIR}/${ARCHIVE_FILE} )
    message(STATUS "${PACKAGE} already downloaded (${TPL_DOWNLOAD_DIR}/${ARCHIVE_FILE})" )
    set(${URL} ${${TPL_DOWNLOAD_DIR}/${ARCHIVE_FILE}} PARENT_SCOPE)
else()
    message(STATUS "${PACKAGE} will be downloaded (${URL})" )
endif()
endfunction(SetURL)
