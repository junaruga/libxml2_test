#include "read_memory_main.h"

/*
 * Copy from nokogiri/ext/nokogiri/html_document.c
 */
static VALUE read_memory( VALUE klass,
                          VALUE string,
                          VALUE url,
                          VALUE encoding,
                          VALUE options )
{
  const char * c_buffer = StringValuePtr(string);
  const char * c_url    = NIL_P(url)      ? NULL : StringValueCStr(url);
  const char * c_enc    = NIL_P(encoding) ? NULL : StringValueCStr(encoding);
  int len               = (int)RSTRING_LEN(string);
  VALUE error_list      = rb_ary_new();
  VALUE document;
  htmlDocPtr doc;

  xmlResetLastError();
  xmlSetStructuredErrorFunc((void *)error_list, Nokogiri_error_array_pusher);

  doc = htmlReadMemory(c_buffer, len, c_url, c_enc, (int)NUM2INT(options));
  xmlSetStructuredErrorFunc(NULL, NULL);

  if(doc == NULL) {
    xmlErrorPtr error;

    xmlFreeDoc(doc);

    error = xmlGetLastError();
    if(error)
      rb_exc_raise(Nokogiri_wrap_xml_syntax_error(error));
    else
      rb_raise(rb_eRuntimeError, "Could not parse document");

    return Qnil;
  }

  document = Nokogiri_wrap_xml_document(klass, doc);
  rb_iv_set(document, "@errors", error_list);
  return document;
}

int main(int argc, const char **argv)
{
  const char *html = "<<a>b";
  char buf[32];
  const char *out = NULL;

  VALUE klass = rb_define_class("Nokogiri::HTML::Document", rb_cObject);
  sprintf(buf, "<html><body>%s", html);
  VALUE string = rb_str_new_cstr(buf);
  VALUE encoding = rb_str_new_cstr("UTF-8");
  VALUE options = (VALUE) 2145;
  VALUE document = read_memory(klass, string, Qnil, encoding, options);
  VALUE document_str = StringValue(document);
  out = StringValueCStr(document_str);
  printf("out: %s\n", out);
}

