// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_CRYPTO_DATA_H_
#define CONTENT_CHILD_WEBCRYPTO_CRYPTO_DATA_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebVector.h"

namespace blink {
class WebArrayBuffer;
}

namespace content {

namespace webcrypto {

// Helper to pass around a range of immutable bytes. This is conceptually
// similar to base::StringPiece, but for crypto byte data.
//
// The data used at construction is NOT owned, and should remain valid as long
// as the CryptoData is being used.
class CONTENT_EXPORT CryptoData {
 public:
  // Constructs empty data.
  CryptoData();

  CryptoData(const unsigned char* bytes, unsigned int byte_length);

  // These constructors do NOT copy the data. Hence the base pointer should
  // remain valid for the lifetime of CryptoData.
  explicit CryptoData(const std::vector<unsigned char>& bytes);
  explicit CryptoData(const std::string& bytes);
  explicit CryptoData(const blink::WebArrayBuffer& buffer);
  explicit CryptoData(const blink::WebVector<unsigned char>& bytes);

  const unsigned char* bytes() const { return bytes_; }
  unsigned int byte_length() const { return byte_length_; }

 private:
  const unsigned char* const bytes_;
  const unsigned int byte_length_;

  DISALLOW_COPY_AND_ASSIGN(CryptoData);
};

}  // namespace webcrypto

}  // namespace content

#endif  // CONTENT_CHILD_WEBCRYPTO_CRYPTO_DATA_H_
