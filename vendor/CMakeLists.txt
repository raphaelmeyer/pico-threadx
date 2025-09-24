include(FetchContent)

set(THREADX_ARCH "cortex_m0")
set(THREADX_TOOLCHAIN "gnu")

FetchContent_Declare(
  threadx
  GIT_REPOSITORY https://github.com/eclipse-threadx/threadx.git
  GIT_TAG v6.4.2_rel
)

FetchContent_MakeAvailable(threadx)
