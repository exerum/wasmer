use wasmer::Memory;
use wasmer_wasi_types::{__WASI_EFAULT, __wasi_errno_t};

pub fn my_deref_array<T: Sized>(memory: &Memory, offset: u32, item_count: u32) -> Result<&mut [T], __wasi_errno_t> {
    let item_size = std::mem::size_of::<T>();
    let array_size_in_bytes = item_size * item_count as usize;
    if offset as usize + array_size_in_bytes > memory.size().bytes().0 {
        return Err(__WASI_EFAULT);
    }
    Ok(
        unsafe {
            std::slice::from_raw_parts_mut(
                (memory.data_ptr() as usize + offset as usize) as *mut T,
                item_count as usize
            )
        }
    )
}

pub fn my_deref_buffer(memory: &Memory, offset: u32, len: u32) -> Result<&mut [u8], __wasi_errno_t> {
    if offset as usize + len as usize > memory.size().bytes().0 {
        return Err(__WASI_EFAULT)
    };
    Ok(unsafe {
        std::slice::from_raw_parts_mut((memory.data_ptr() as usize + offset as usize) as *mut u8, len as usize)
    })
}