# Custom Interrupt Handler Management

when defining `DDL_INTERRUPTS_CUSTOM_HANDLER_MANAGEMENT = 1`, the DDL will not provide a implementation for `enIrqRegistration` and `enIrqResign` functions.
This allows you to implement your own interrupt management, which may be useful when using a vector table in ram.

> [!CAUTION]
> do **not** enable this option unless you know exactly what you're doing.

> [!CAUTION]
> the `DDL_EXINT_NMI_SWI_ENABLE` ddl depends on the `NMI_IrqHandler` getting called when a NMI occurs.
> please check your specific use case before enabling this option.
