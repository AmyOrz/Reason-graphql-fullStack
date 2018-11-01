external convertSelectToJsObj : MySql2.Select.t => Js.t({..}) = "%identity";

external convertParamToJsObj : 'a => Js.t({..}) = "%identity";